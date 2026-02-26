#include "header.h"

char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
						"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
						"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", "jobs", "fg", "bg", NULL};

char cmd[20];

/*******************************************************************************************************************************************************************
 * Function Name : get_command
 * Description   : Extracts the first token (command) from the given
 *                 input string using space as the delimiter.
 *                 - Uses strtok() to split the input string.
 *                 - Copies the first token into a global/local buffer.
 *                 - Returns the extracted command.
 *                 - Returns NULL if input string is empty or no token found.
 * Input         : input_string – complete command line entered by user
 * Return        : Pointer to extracted command string
 *                 NULL – if no valid command is found
 *******************************************************************************************************************************************************************/
char *get_command(char *input_string)
{
    char string[50];
    strcpy(string, input_string);
    char *token = strtok(string, " ");

    if (token == NULL)
        return NULL;

    strcpy(cmd, token);
    
    return cmd;
}

/*******************************************************************************************************************************************************************
 * Function Name : check_command_type
 * Description   : Determines whether the given command is an
 *                 internal (built-in) command, an external command,
 *                 or an invalid command.
 *                 - Compares the input command with the list of
 *                   built-in commands.
 *                 - If not found, compares with the list of
 *                   external commands.
 *                 - Returns appropriate command type identifier.
 * Input         : command – command string entered by the user
 * Return        : BUILTIN     – if command is an internal command
 *                 EXTERNAL    – if command is an external command
 *                 NO_COMMAND  – if command is not recognized
 *******************************************************************************************************************************************************************/
int check_command_type(char *command)
{
    /* Check for internal command.*/
    for (int i = 0; builtins[i] != NULL; i++)
    {
        if (strcmp(command, builtins[i]) == 0)
        {
            // printf("builtin : %s\n", builtins[i]);
            return BUILTIN;
        }
    }
    
    /* Check for external command.*/
    for (int i = 0; i < 152; i++)
    {
        if (strcmp(exte_cmds[i], command) == 0)
        {
            // printf("external : %s\n", exte_cmds[i]);
            return EXTERNAL;
        }
    }

    /* If not a valid command.*/
    return NO_COMMAND;
}

/*******************************************************************************************************************************************************************
 * Function Name : execute_internal_commands
 * Description   : Executes built-in (internal) shell commands such as
 *                 exit, pwd, and cd.
 *                 - "exit" terminates the shell.
 *                 - "pwd" prints the current working directory.
 *                 - "cd" changes the current working directory
 *                   to the specified path and displays the updated path.
 * Input         : input_string – command entered by the user
 * Return        : None (void)
 *******************************************************************************************************************************************************************/
void execute_internal_commands(char *input_string)
{
    if (strcmp(input_string, "exit") == 0)
        exit(0);
    else if (strcmp(input_string, "pwd") == 0)
    {
        char buff[100];
        if (getcwd(buff, sizeof(buff)) != NULL)
            printf("%s\n", buff);
        else
            perror("getcwd");
    }
    else if (strncmp(input_string, "cd", 2) == 0)
    {
        chdir(input_string + 3);

        char buff[100];
        if (getcwd(buff, sizeof(buff)) != NULL)
            printf("%s\n", buff);
        else
            perror("getcwd");
    }
 
}

void execute_external_commands(char *input_string)
{
    char *cmd_list[20];
    int cmd_count = 0;

    cmd_list[cmd_count] = strtok(input_string, "|");

    while (cmd_list[cmd_count] != NULL)
    {
        cmd_count++;
        cmd_list[cmd_count] = strtok(NULL, "|");
    }

    if (cmd_count < 2)
    {
        // No pipe → execute normally
        char *args[20];

        while (*cmd_list[0] == ' ')
        cmd_list[0]++;

        split_arguments(cmd_list[0], args);

        pid_t pid = fork();

        if (pid == 0)
        {
            execvp(args[0], args);
            perror("Execution failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL);
        }

        return;
    }

    /* Create required pipes (number of commands - 1) */
    int pipefd[cmd_count - 1][2];

    for (int i = 0; i < cmd_count - 1; i++)
    {
        if (pipe(pipefd[i]) == -1)
        {
            perror("Pipe error");
            exit(EXIT_FAILURE);
        }
    }

    /* Create processes */
    for (int i = 0; i < cmd_count; i++)
    {
        pid_t pid = fork();

        if (pid == 0)   // Child process
        {
            char *args[20];

            /* Remove leading spaces */
            while (*cmd_list[i] == ' ')
                cmd_list[i]++;

            split_arguments(cmd_list[i], args);

            if (i == 0)
            {
                // First command: output to first pipe
                dup2(pipefd[i][1], STDOUT_FILENO);
            }
            else if (i == cmd_count - 1)
            {
                // Last command: input from previous pipe
                dup2(pipefd[i - 1][0], STDIN_FILENO);
            }
            else
            {
                // Middle command
                dup2(pipefd[i - 1][0], STDIN_FILENO);
                dup2(pipefd[i][1], STDOUT_FILENO);
            }

            /* Close all pipe ends */
            for (int j = 0; j < cmd_count - 1; j++)
            {
                close(pipefd[j][0]);
                close(pipefd[j][1]);
            }

            execvp(args[0], args);
            perror("Execution failed");
            exit(EXIT_FAILURE);
        }
    }

    /* Parent closes pipes */
    for (int i = 0; i < cmd_count - 1; i++)
    {
        close(pipefd[i][0]);
        close(pipefd[i][1]);
    }

    /* Wait for all children */
    for (int i = 0; i < cmd_count; i++)
    {
        wait(NULL);
    }
}

/* Split a single command into arguments for execvp */
void split_arguments(char *cmd, char **args)
{
    int i = 0;

    args[i] = strtok(cmd, " ");
    while (args[i] != NULL)
    {
        i++;
        args[i] = strtok(NULL, " ");
    }
}