/*############################################################################################### 
 *
 *           Author         : 
 *           Date           : 
 *           File           : msh.c©
 *           Descriptions   : minishell program capable of executing commands and job controll
 *           Objective      :
 *           Usage          :
 *           Output         :
 *
###############################################################################################*/
#include "header.h"

char prompt[25] = "minishell$ ";
char input_string[25];
char *exte_cmds[152];

job_t *job_list = NULL;
int job_count = 1;

pid_t pid;
pid_t foreground_pid = -1;
pid_t child_pid;

int status;
int last_exit_status = 0;  // Stores exit status of last executed foreground command ($?).

int main()
{
	system("clear");
	
	scan_input(prompt, input_string);
}
