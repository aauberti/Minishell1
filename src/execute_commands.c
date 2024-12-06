#include "minishell.h"

int ft_is_builtin_commands(const char *command)
{
    if (ft_strncmp("exit", command, 4) == 0)
        return (0);
    if (ft_strncmp("pwd", command, 3) == 0)
        return (0);
    if (ft_strncmp("history", command, 8) == 0)
        return (0);
    if (ft_strncmp("echo", command, 4) == 0)
        return (0);
    if (ft_strncmp("cd", command, 2) == 0)
        return (0);
    if (ft_strncmp("export", command, 6) == 0)
        return (0);
    if (ft_strncmp("unset", command, 5) == 0)
        return (0);
    if (ft_strncmp("env", command, 3) == 0)
        return (0);
    return (1);
}

int handle_builtin_commands(t_info *shell, t_commands commands, int end)
{
    if (ft_strncmp("exit", commands.commands[0], 4) == 0)
        exit_shell(shell, commands, end);
    if (ft_strncmp("pwd", commands.commands[0], 3) == 0)
        pwd_shell(shell, commands, end);
    if (ft_strncmp("history", commands.commands[0], 8) == 0)
        history_shell(shell, commands, end);
    if (ft_strncmp("echo", commands.commands[0], 4) == 0)
        echo_shell(shell, commands, end);
    if (ft_strncmp("cd", commands.commands[0], 2) == 0)
        cd_shell(shell, commands, end);
    if (ft_strncmp("export", commands.commands[0], 6) == 0)
        export_shell(shell, commands, end);
    if (ft_strncmp("unset", commands.commands[0], 5) == 0)
        unset_shell(shell, commands, end);
    if (ft_strncmp("env", commands.commands[0], 3) == 0)
        env_shell(shell, commands, end);
    return (0);
}

void ft_execute_commands(t_info *shell)
{
    int cmd_count;
    int pipe_fd[2];
    t_commands *current_cmds;

    cmd_count = 0;
    if (!shell->commands)
        return ;
    current_cmds = shell->commands->content;
    if (shell->commands->next == NULL && current_cmds->commands != NULL && ft_is_builtin_commands(current_cmds->commands[0]) == 0 &&
        ft_strncmp("env", current_cmds->commands[0], 3) != 0)
    {
        handle_builtin_commands(shell, *current_cmds, 0);

    }
}