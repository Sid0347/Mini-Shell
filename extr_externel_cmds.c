#include "header.h"

/*******************************************************************************************************************************************************************
 * Function Name : extract_external_commands
 * Description   : Reads external command names from the file "ext_cmds.txt"
 *                 and stores them into the provided array of character pointers.
 *                 - Opens the file in read mode.
 *                 - Reads each command line using fgets().
 *                 - Dynamically allocates memory for each command.
 *                 - Copies the command into allocated memory.
 *                 - Terminates the program if file opening or memory allocation fails.
 * Input         : external_commands – array of character pointers used
 *                 to store dynamically allocated external command strings
 * Return        : None (void)
 *******************************************************************************************************************************************************************/
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
    while(fgets(cmd, 30, fptr))
    {
        int cmd_len = strlen(cmd);
        external_commands[i] = malloc((cmd_len + 1) * sizeof(char));
        if (external_commands[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        cmd[strcspn(cmd, "\n")] = '\0'; /* It removes the newline character (\n) that fgets() stores in the string.*/
        strcpy(external_commands[i], cmd);
        i++;
    }
    
}