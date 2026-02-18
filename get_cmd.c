#include "header.h"
char cmd[20];

char *get_command(char *input_string)
{
    char *token = strtok(input_string, " ");

    if (token == NULL)
        return NULL;

    strcpy(cmd, token);
    
    return cmd;
}
