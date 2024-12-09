/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:10:27 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/09 13:30:36 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void configure_pipe(t_info *shell, int fd[2], int *count)
{
    t_commands *command;
    t_commands *next_command;
    t_list *current;

    current = shell->commands;
    while (current)
    {
        (*count)++;
        command = current->content;
        if (current->next != NULL)
        {
            next_command = current->next->content;
            setup_pipe_between_commands(command, next_command, fd);
        }
        current = current->next;
    }
}

void free_execute_data(t_info *shell)
{
    if (shell->commands)
        ft_lstclear(&shell->commands, free_command);
    if (shell->pids)
    {
        free(shell->pids);
        shell->pids = NULL;
    }
}

int ft_is_builtin_commands(const char *command)
{
    if (ft_strncmp("exit", command, 5) == 0)
        return (0);
    if (ft_strncmp("pwd", command, 4) == 0)
        return (0);
    if (ft_strncmp("history", command, 8) == 0)
        return (0);
    if (ft_strncmp("echo", command, 5) == 0)
        return (0);
    if (ft_strncmp("cd", command, 3) == 0)
        return (0);
    if (ft_strncmp("export", command, 7) == 0)
        return (0);
    if (ft_strncmp("unset", command, 6) == 0)
        return (0);
    if (ft_strncmp("env", command, 4) == 0)
        return (0);
    return (1);
}

int handle_builtin_commands(t_info *shell, t_commands commands, int end)
{
    if (ft_strncmp("exit", commands.command[0], 5) == 0)
        exit_shell(shell, commands);
    if (ft_strncmp("pwd", commands.command[0], 4) == 0)
        pwd_shell(shell, commands, end);
    if (ft_strncmp("history", commands.command[0], 8) == 0)
        history_shell(shell, commands, end);
    if (ft_strncmp("echo", commands.command[0], 5) == 0)
        echo_shell(shell, commands, end);
    if (ft_strncmp("cd", commands.command[0], 3) == 0)
        cd_shell(shell, commands, end);
    if (ft_strncmp("export", commands.command[0], 7) == 0)
        export_shell(shell, commands, end);
    if (ft_strncmp("unset", commands.command[0], 5) == 0)
        unset_shell(shell, commands, end);
    if (ft_strncmp("env", commands.command[0], 4) == 0)
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
    if (shell->commands->next == NULL && current_cmds->command != NULL 
        && ft_is_builtin_commands(current_cmds->command[0]) == 0 
        && ft_strncmp("env", current_cmds->command[0], 3) != 0)
    {
        handle_builtin_commands(shell, *current_cmds, 0);
        free_execute_data(shell);
        return ;
    }
    configure_pipe(shell, pipe_fd, &cmd_count);
    shell->pids = malloc(sizeof(int) * cmd_count);
    if (shell->pids == NULL)
        manage_exit(shell, "exec", 1, 0);
    run_command_in_pipeline(shell, cmd_count);
    wait_for_processes(shell, cmd_count);
    free_execute_data(shell);
}