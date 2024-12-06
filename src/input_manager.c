/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebervas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:49 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/05 10:46:16 by ebervas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_create_token(char *str)
{
    int     i;
    char    **tokens;
    char    **sign;

    i = 0;
    tokens = ft_split_str(str, " ");
    while (tokens && tokens[i])
    {
        sign = ft_split_in_word(tokens[i], "<|>");
        insert_in_word(&tokens, sign, i);
        i = i + ft_tab_len(sign) - 1;
        ft_freetab(&sign);
        i++;
    }
    return (tokens);
}

void    input_manager(t_info *shell, char *str)
{
    char    **tokenize;

    tokenize = ft_create_token(str);
    free(str);
    if(!tokenize)
    {
        manage_exit(shell, NULL, UNCLOSED_QUOTE, 0);
        return ("");
    }
    ft_expand(shell, tokenize);
    shell->commands = ft_update_list(shell, tokenize, -1);
    return (shell);
}