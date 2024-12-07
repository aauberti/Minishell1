/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebervas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:53 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/07 16:31:01 by ebervas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int shell_signal;

int main(int argc, char **argv, char **envp)
{
    char    *str;
    t_info  shell;
    if (argc != 1)
    {
        printf("Error: Too many arguments\n");
        return (1);
    }
    if(argv[1] != NULL)
    {
        printf("Error: Arguments not supported\n");
        return (1);
    }   
    if (!envp || !envp[0])
    {
        printf("Error: No environment variables provided\n");
        return (1);
    }
    t_hashmap *table = init_hashmap(envp);
    if (!table)
    {
        printf("Error: Failed to initialize hashmap\n");
        return (1);
    }
    hashmap_print_table(table, 0);
    init_shell(&shell, argv, envp);
    while (1)
    {
        str = prompt(&shell);
        if (!str)
            break;
        input_manager(&shell, str);
         ft_execute_commands(&shell);
    }
}