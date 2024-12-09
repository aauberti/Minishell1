/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:32:44 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/09 09:35:29 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_print_error2(int error)
{
    if (error == COMMAND_NOT_FOUND)
        ft_putstr_fd(" command not found", 2);
    else if (error == IS_A_DIRECTORY)
        ft_putstr_fd(" is a directory", 2);
    else if (error == HISTORY_BAD_ARG)
        ft_putstr_fd(" numeric argument required", 2);
    else if (error == HISTORY_BAD_ARGS)
        ft_putstr_fd(" too many arguments", 2);
    else if (error == FILE_NOT_FOUND || error == CD_ERROR)
        ft_putstr_fd(" no such file or directory", 2);
    else if (error == NOT_A_DIRECTORY)
        ft_putstr_fd(" not a directory", 2);
}

void ft_print_error(char *argument, int error)
{
    ft_putstr_fd("minishell: ", 2);
    if(error == INVALID_ARGS)
        ft_putstr_fd("no argument found: ", 2);
    else if(error == FORK_ERROR)
        ft_putstr_fd("fork error: ", 2);
    else if(error == UNCLOSED_QUOTE)
        ft_putstr_fd("unclosed quote: ", 2);
    else if(error == NO_PERMISSION)
        ft_putstr_fd("permission denied: ", 2);
    else if(error == PIPE_ERROR)
        ft_putstr_fd("pipe error: ", 2);
    else if(error == SYNTAX_ERROR)
        ft_putstr_fd("syntax error: ", 2);
    else if(error == HASH_TABLE_FULL)
        ft_putstr_fd("hash table full: ", 2);
    else if(error == OUT_OF_MEMORY)
        ft_putstr_fd("out of memory: ", 2);
    else if (error == HISTORY_BAD_ARG || error == HISTORY_BAD_ARGS)
        ft_putstr_fd("history: ", 2);
    if (argument)
        ft_putstr_fd(argument, 2);
    ft_print_error2(error);
    ft_putstr_fd("\n", 2);
}