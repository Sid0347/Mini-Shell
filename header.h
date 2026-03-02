#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

/*---------------------------------------------------------------------------------------------------
 * Command type definitions
 *-------------------------------------------------------------------------------------------------*/
#define BUILTIN     1   // Shell built-in command
#define EXTERNAL    2   // External system command
#define NO_COMMAND  3   // Unrecognized command

/*---------------------------------------------------------------------------------------------------
 * Job states
 *-------------------------------------------------------------------------------------------------*/
#define STOPPED 4        // Stopped process
#define RUNNING 5        // Running in background
#define DONE    6        // Process finished execution

/*---------------------------------------------------------------------------------------------------
 * ANSI color codes
 *-------------------------------------------------------------------------------------------------*/
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*---------------------------------------------------------------------------------------------------
 * Job structure
 *-------------------------------------------------------------------------------------------------*/
typedef struct job
{
    int job_id;             // Unique job ID
    pid_t pid;              // Process ID
    char command[100];      // Command string
    int state;              // STOPPED, RUNNING, DONE
    struct job *next;       // Pointer to next job
} job_t;

/*---------------------------------------------------------------------------------------------------
 * Global variables
 *-------------------------------------------------------------------------------------------------*/
extern char prompt[25];           
extern char input_string[25];     

extern char *exte_cmds[152];      
extern pid_t pid;                  
extern pid_t foreground_pid;       
extern pid_t child_pid;            

extern int status;                 
extern int last_exit_status;       

extern job_t *job_list;            
extern int job_count;              

/*---------------------------------------------------------------------------------------------------
 * Function declarations
 *-------------------------------------------------------------------------------------------------*/
void extract_external_commands(char **external_commands); // Fills exte_cmds[] with system commands

void scan_input(char *prompt, char *input_string);      // Reads input and executes commands
char *get_command(char *input_string);                  // Extracts command from input string
int check_command_type(char *command);                 // Returns command type: BUILTIN/EXTERNAL/NO_COMMAND

void execute_internal_commands(char *input_string);    // Executes built-in commands
void execute_external_commands(char *input_string);    // Executes external commands

void split_arguments(char *cmd, char **args);          // Splits command string into arguments
void insert_at_first(pid_t pid, char *cmd);            // Adds job to the job list
void signal_handler(int sig_num);                      // Handles SIGINT, SIGTSTP, SIGCHLD

#endif