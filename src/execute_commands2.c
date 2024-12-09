#include "minishell.h"

void redirect_io_for_command(t_commands *command)
{
    if (command->fd2 != 1)
        dup2(command->fd2, 1);
    if (command->fd1 != 0)
        dup2(command->fd1, 0);
}

void create_child_process(t_info *shell, t_commands *command, int *pids, int count)
{
    pids[count] = fork();
    setup_execution_signals_handler();
    if (pids[count] == -1)
        manage_exit(shell, NULL, FORK_ERROR, 0);
    if (pids[count] == 0)
    {
        redirect_io_for_command(command);
        ft_run_command(shell, command);
    }
    else
    {
        if (command->fd2 != 1)
            close(command->fd2);
        if (command->fd1 != 0)
            close(command->fd1);
    }
}

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

    current = shell->commands;
    index = 0;
    while (current && index < count)
    {
        signal(SIGINT, SIG_IGN);
        create_child_process(shell, current->content, shell->pids, index);
        current = current->next;
        index++;
    }
}
