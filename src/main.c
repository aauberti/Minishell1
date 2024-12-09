/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:53 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/08 23:30:07 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int shell_signal;

int main(int argc, char **argv, char **envp)
{
    char    *str;
    t_info  shell;
    
    if (argc != 1)
        manage_exit(NULL, argv[1], INVALID_ARGS, 1);
    init_shell(&shell, argv, envp);
    while (1)
    {
        shell_signal = 0;
        setup_input_signals_handler();
        str = prompt(&shell);
        if (!str)
            break;
        input_manager(&shell, str);
        ft_execute_commands(&shell);
        if (shell_signal == SIGINT)
            shell.exit_status = 128 + shell_signal;
    }
    manage_exit(&shell, NULL, 0, 1);
    return (0);
}