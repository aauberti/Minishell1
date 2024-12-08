/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:15 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/08 12:36:09 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    update_tab(char **tab, int index, int tab_len)
{
    int     i;
    char    *temp;

    i = 0;
    while (i < tab_len)
    {
        if (i < index)
            i++;
        else
        {
            temp = tab[i];
            tab[i] = tab[i + 1];
            tab[i + 1] = temp;
            i++;
        }
    }
}

char    *handle_variable_home(char   *token, int index, int state[2], char *home)
{
    char    *loc;
    char    *temp;

    state[0] = 0;
    state[1] = 0;

    while(token && token[++index])
    {
        state[0] = (state[0] + (!state[1] && token[index] == '\'')) % 2;
        state[1] = (state[1] + (!state[0] && token[index] == '\"')) % 2;
        if (!state[0] && !state[1] && token[index] == '~' && token[index + 1] != '~' && (index == 0 || token[index - 1] != '$'))
        {
            temp = ft_substr(token, 0, index);
            loc = ft_strjoin(temp, home);
            free(temp);
            temp = ft_substr(token, index + 1, ft_strlen(token));
            free(token);
            token = ft_strjoin(loc, temp);
            free(temp);
            free(loc);
            return (handle_variable_home(token, index + ft_strlen(home) - 1, state, home));
        }
    }
    free(home);
    return (token);
}