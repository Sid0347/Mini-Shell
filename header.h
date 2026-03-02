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
 

#define BUILTIN		1
#define EXTERNAL	2
#define NO_COMMAND  3

#define STOPPED 4
#define RUNNING 5
#define DONE 6

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct job
{
    int job_id;
    pid_t pid;
    char command[100];
    int state;   // STOPPED, RUNNING, DONE
    struct job *next;
} job_t;

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

void scan_input(char *prompt, char *input_string);
char *get_command(char *input_string);

void copy_change(char *prompt, char *input_string);

int check_command_type(char *command);
void echo(char *input_string, int status);
void execute_internal_commands(char *input_string);
void execute_external_commands(char *input_string);
void split_arguments(char *cmd, char **args);
void insert_at_first(pid_t pid, char *cmd);

void signal_handler(int sig_num);
void extract_external_commands(char **external_commands);

// void print_list(struct node *head);
#endif
