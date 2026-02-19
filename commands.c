#include "header.h"

char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
						"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
						"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help"};

char cmd[20];

char *get_command(char *input_string)
{
    char *token = strtok(input_string, " ");

    if (token == NULL)
        return NULL;

    strcpy(cmd, token);
    
    return cmd;
}

int check_command_type(char *command)
{
    /* Check for internal command.*/
    for (int i = 0, builtins[i] != NULL; i++)
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