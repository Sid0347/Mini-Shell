#include "minishell.h"

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
        if (foreground_pid > 0)
        {
            kill(foreground_pid, SIGINT);
        }
        else
        {
            write(STDOUT_FILENO, "\n", 1);
            write(STDOUT_FILENO, prompt, strlen(prompt));
        }
    }
    if (signum == SIGTSTP)
    {
        if (foreground_pid > 0)
        {
            kill(foreground_pid, SIGTSTP);
        }
        else
        {
            write(STDOUT_FILENO, "\n", 1);
            write(STDOUT_FILENO, prompt, strlen(prompt));
        }
    }
    if (signum == SIGCHLD)
    {
        int status;
        while ((child_pid = waitpid(-1, &status, WNOHANG)) > 0)
        {
            job_t *temp = job_list;

            while (temp != NULL)
            {
                if (temp->pid == child_pid)
                {
                    temp->state = DONE;   // mark as finished
                    break;
                }
                temp = temp->next;
            }
        }
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
void insert_at_first(pid_t pid, char *cmd)
{
    job_t *new = malloc(sizeof(job_t));
    if (new == NULL)
    {
        perror("malloc");
        return;
    }
    new->job_id = job_count++;
    new->pid = pid;
    strcpy(new->command, cmd);

    new->state = STOPPED;

    new->next = job_list;
    job_list = new;
}
