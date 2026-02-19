#include "header.h"

char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
						"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
						"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help"};

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
    char *token = strtok(input_string, " ");

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
            return BUILTIN;
    }

    /* Check for external command.*/
    for (int i = 0; i < 152; i++)
    {
        if (strcmp(command, exte_cmds[i]) == 0)
            return EXTERNAL;
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