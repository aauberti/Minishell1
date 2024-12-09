/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:10:05 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/09 11:16:37 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_is_valid_n_flag(char *cmd)
{
    int i;

    i = 1;
    if (!cmd)
        return (0);
    if (cmd[0] != '-' || cmd[1] != 'n')
        return (0);
    while (cmd[i] != '\0')
    {
        if (cmd[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

void	echo_shell(t_info *shell, t_commands commands, int end)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (commands.command[1] != NULL)
    {
        if (ft_is_valid_n_flag(commands.command[i]) == 0 || j == 1)
        {
            j = 1;
            ft_putstr_fd(commands.command[i], commands.fd2);
            if (commands.command[i + 1] != NULL)
                ft_putstr_fd(" ", commands.fd2);
        }
        i++;
    }
    if (ft_is_valid_n_flag(commands.command[1]) == 0)
        ft_putstr_fd("\n", commands.fd2);
    manage_exit(shell, NULL, 0, end);
}