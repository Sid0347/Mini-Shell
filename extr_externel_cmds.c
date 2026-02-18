#include "header.h"

void extract_external_commands(char **external_commands)
{
    FILE *fptr = fopen("ext_cmds.txt", "r");
    if (fptr == NULL)
    {
        perror("Open : ");
        exit(1);
    }

    char cmd[30];
    int i = 0;
    while(fgets(cmd, 20, fptr))
    {
        int cmd_len = strlen(cmd);
        external_commands[i] = malloc((cmd_len + 1) * sizeof(char));
        if (external_commands[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        strcpy(external_commands[i], cmd);
        i++;
    }
    
}