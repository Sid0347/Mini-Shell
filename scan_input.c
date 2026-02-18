#include "header.h"

char *exte_cmds[152];

void scan_input(char *prompt, char *input_string)
{
	extract_external_commands(exte_cmds);
	while (1)
	{
		printf("%s", prompt);
		scanf("%[^\n]", input_string);
		getchar();	

		/* Check input have 'PS1=' or not.*/
		if (strncmp(input_string, "PS1=", 4) == 0)
		{
			for (int i = 4; input_string[i] != '\0'; i++)
			{
				if (input_string[i] == ' ' && input_string[i + 1] != ' ' && input_string[i + 1] != '\0')
				{
					printf("%s: command not found\n", input_string + 4);
					break;
				}	
			}
			strcpy(prompt, input_string);
		}
		else
		{
			char *cmd = get_command(input_string);
			if (cmd == NULL)
			{
				// printf("Invalid command.\n");
				continue;
			}
			printf("here : %s\n", cmd);
			// int type = check_command_type(cmd);
			// if(type == BUILTIN)
			// {
			// 	execute_internal_commands()
			// }
		}
	}
}



