#include "header.h"

char *exte_cmds[152];
pid_t pid;
int status;

void scan_input(char *prompt, char *input_string)
{
	extract_external_commands(exte_cmds);
	/* Signal Handling at the input waiting time.*/
	signal(SIGINT, signal_handler);	  /* ctrl + c */
	signal(SIGTSTP, signal_handler); /* ctrl + z */
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
			int type = check_command_type(cmd);
			if(type == BUILTIN)
			{
				// printf("Built in cmd\n");
				execute_internal_commands(input_string);
			}
			else if(type == EXTERNAL)
			{
				// printf("External cmd\n");
				pid = fork();

				if(pid > 0)
				{
					waitpid(pid, &status, WUNTRACED);
				}
				if (pid == 0)
				{
					/* Signal Handling at the command execution time.*/
					signal(SIGINT, SIG_DFL);	  /* ctrl + c */
					signal(SIGTSTP, SIG_DFL); /* ctrl + z */
					execute_external_commands(input_string);

				}
			}
			else
			{
				// printf("heee\n");
				printf("No command found\n");
			}
		}
	}
}



