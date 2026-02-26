#include "header.h"

/*******************************************************************************************************************************************************************
 * Function Name : signal_handler
 * Description   : Handles signals received by the shell process.
 *                 - SIGINT  : If no child process is running, redisplays the prompt.
 *                 - SIGTSTP : If a child is running, stores its PID; otherwise redisplays the prompt.
 *                 - SIGCHLD : Reaps terminated child processes to prevent zombies.
 * Input         : signum – signal number received
 * Return        : None (void)
 *******************************************************************************************************************************************************************/
void signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        if (pid == 0)
            printf("%s", prompt);
    }
    if (signum == SIGTSTP)
    {
        if (pid == 0)
            printf("%s", prompt);
        else if (pid != 0)
        {
            insert_at_first(pid);
        }
    }
    if (signum == SIGCHLD)
    {
        waitpid(-1, &status, WNOHANG);
    }
}

/*******************************************************************************************************************************************************************
 * Function Name : insert_at_first
 * Description   : Inserts a new node at the beginning of the linked list
 *                 to store details of a stopped/background process.
 *                 Allocates memory for a new node, stores the process PID
 *                 and corresponding command, and updates the head pointer.
 * Input         : proc_pid – Process ID of the child process
 * Return        : None (void)
 *******************************************************************************************************************************************************************/
void insert_at_first(pid_t proc_pid)
{
    struct node *newnode = malloc(sizeof(struct node));

    newnode->proc_pid = proc_pid;
    strcpy(newnode->cmd, input_string);
    newnode->next = head;
    head = newnode;
}

