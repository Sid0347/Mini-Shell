#include "header.h"

void scan_input(char *prompt, char *input_string)
{
	while (1)
	{
		printf("%s", prompt);
		scanf("%[^\n]", input_string);

		/* Check input have 'PS1=' or not.*/
		if (strncmp(input_string, "PS1=", 4) == 0)
		{
			for (int i = 4; input_string[i] != '\0'; i++)
			{
				if (input_string[i] == ' ' && input_string[i + 1] != ' ' && input_string[i + 1] != '\0')
				{
					printf("%s: command not found\n", input_string + 4);
				}	
			}
			strcpy(prompt, input_string);
			// break;
		}
		else
		{
			printf("%s: command not found\n", input_string + 4);
		}
	}
}
