/*############################################################################################### 
 *
 *           Project        : MiniShell
 *           Author         : Siddharth Gaikwad
 *           Date           : 2026-02-17
 *           File           : main.c
 *           Description    : A custom mini-shell program that replicates basic shell functionality.
 *                            Supports execution of internal (built-in) and external commands.
 *           Objective      : 
 *           				   - Provide a simple command-line interface for executing commands.
 *                             - Manage foreground and background processes with proper signal handling.
 *                             - Maintain job lists and track command exit status.
 *           Key Features   : 
 *                             1. Built-in commands: cd, pwd, echo, exit, fg, bg, jobs, etc.
 *                             2. External command execution using fork() and execvp().
 *                             3. Pipeline support using multiple pipes and child processes.
 *                             4. Job control with STOPPED, RUNNING, and DONE states.
 *                             5. Signal handling: SIGINT, SIGTSTP, SIGCHLD.
 *                             6. Prompt customization with PS1.
 *           Usage          : Compile with gcc and run the executable. Commands can be entered
 *                            at the prompt 'minishell$ '. Supports background jobs using '&'.
 *           Output         : Executes commands, displays outputs, handles pipelines, tracks
 *                            stopped/terminated jobs, and maintains last exit status ($?).
 *
###############################################################################################*/
#include "minishell.h"

/* All global variables.*/
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
