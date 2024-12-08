/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:46 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/08 12:04:24 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info  *valid_env(t_info *shell, char **argv)
{
    char    *temp;
    int     nb;

    if (!cmds_in_hashmap(shell->env, "PATH"))
        insertion_in_hashmap(shell->env, "PATH", "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", 0);
    if (!cmds_in_hashmap(shell->env, "_"))
        insertion_in_hashmap(shell->env, "_", argv[0], 0);
    nb = 1;
    if (!cmds_in_hashmap(shell->env, "PWD"))
    {
        temp = getcwd(NULL, 0);
        insertion_in_hashmap(shell->env, "PWD", temp, 0);
        free(temp);
    }
    temp = cmds_in_hashmap(shell->env, "SHLVL");
    if (temp && ft_atoi(temp) > 0)
        nb = ft_atoi(temp) + 1;
    temp = ft_itoa(nb);
    insertion_in_hashmap(shell->env, "SHLVL", temp, 0);
    free(temp);
    return (shell);
}

void create_and_store_pid(t_info *shell)
{
    pid_t   pid;

    pid = fork();
    if (pid < 0)
        manage_exit(shell, NULL, FORK_ERROR, 1);
    if (pid == 0)
        manage_exit(shell, NULL, 1, 1);
    waitpid(pid, NULL, 0);
    shell->pid = pid - 1;
}
void    init_shell(t_info   *shell, char **argv, char **envp)
{
    shell->env = init_hashmap(envp);
    shell->history = NULL;
    shell->commands = NULL;
    shell->pid = 0;
    shell->pids = NULL;
    shell->old_pwd = NULL;
    shell->uid = 0;
    shell->exit_status = 0;
    valid_env(shell, argv);
    create_and_store_pid(shell);
}