#include "minishell.h"

void wait_for_processes(t_info *shell, int count)
{
    int index;
    int status;

    index = 0;
    while (index < count - 1)
    {
        waitpid(shell->pids[index], &status, 0);
        index++;
    }
    waitpid(shell->pids[index], &status, 0);
    if (WIFEXITED(status))
        shell->exit_status = WEXITSTATUS(status);
}

void setup_pipe_between_commands(t_commands *commands, t_commands *next_commands, int *fd)
{
    pipe(fd);
    if (commands->fd2 == 1)
        commands->fd2 = fd[1];
    if (next_commands->fd1 == 0)
        next_commands->fd1 = fd[0];
    if (commands->fd2 != fd[1])
        close(fd[1]);
    if (next_commands->fd1 != fd[0])
        close(fd[0]);
}

void run_command_in_pipeline(t_info *shell, int count)
{
    int index;
    t_list *current;

    current = shell->command;
    index = 0;
    while (current && index < count)
    {
        signal(SIGINT, SIG_IGN);
        create_child_process(shell, current->content, shell->pids, index);
        current = current->next;
        index++;
    }
}