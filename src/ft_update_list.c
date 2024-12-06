/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:27 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/04 10:32:47 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **ft_tabcpy(char **tokenize)
{
    char    **new;
    int     len;
    int     index;

    if (!tokenize || tokenize[0])
        return (NULL);
    len = ft_tab_len(tokenize);
    new = malloc((len + 1) * sizeof(char *));
    if (!new)
        return (NULL);
    index = -1;
    while (tokenize[++index])
    {
        new[index] = ft_strdup(tokenize[index]);
        if (!new[index])
        {
            ft_freetab(&new);
            return (NULL);
        }
    }
    new[index] = NULL;
    return (new);

}

int     ft_len_token(char *token)
{
    int     index;
    int     state[2];
    int     cpt;

    state[0] = 0;
    state[1] = 0;
    cpt = 0;
    index =-1;
    while (token[++index])
    {
        state[0] = (state[0] + (!state[1] && token[index] == '\'')) % 2;
        state[1] = (state[1] + (!state[0] && token[index] == '\"')) % 2;
        if ((!state[1] && token[index] == '\'') || (!state[0] && token[index] == '\"'))
            cpt++;
    }
    if (state[0] || state[1])
        return (-1);
    return (cpt);
}

char    *ft_cut_token(char *token)
{
    char    *new_token;
    int     state[2];
    int     index[2];
    int     cpt;

    index[0] = -1;
    index[1] = -1;
    state[0] = 0;
    state[1] = 0;
    cpt = ft_len_token(token);
    if (!token || cpt == -1)
        return (NULL);
    new_token = malloc((ft_strlen(token) - cpt + 1) * sizeof(char));
    if (!new_token)
        return (NULL);
    while (token[++index[0]])
    {
        state[0] = (state[0] + (!state[1] && token[index[0]] == '\'')) % 2;
        state[1] = (state[1] + (!state[0] && token[index[0]] == '\"')) % 2;
        if ((state[1] || token[index[0]] == '\'') && (state[0] || token[index[0]] == '\"') && ++index[1] >= 0)
            new_token[index[1]] = token[index[0]];
    }
    new_token[++index[1]] = '\0';
    return (new_token);
}

char    **ft_cut_tokenize(char **tokenize)
{
    char    *temp;
    char    **new_tokens;
    int     index;

    new_tokens = ft_tabcpy(tokenize);
    index = -1;
    while (new_tokens && new_tokens[++index])
    {
        temp = ft_cut_token(new_tokens[index]);
        free(new_tokens[index]);
        new_tokens[index] = temp;
    }
    return (new_tokens);
}

t_list  *ft_list_update(t_info *shell, char **tokenize, int index)
{
    t_list *commands[2];
    char    **temp[2];

    commands[0] = NULL;
    temp[0] = ft_cut_tokenize(tokenize);
    temp[1] = tokenize;
    while (tokenize[++index])
    {
        commands[1] = ft_lstlast(commands[0]);
        if (index == 0 || (tokenize[index][0] == '|' && tokenize[index + 1] && tokenize[index +1][0]))
        {
            index += tokenize[index][0] == '|';
            ft_lstadd_back(&commands[0], ft_lstnew(ft_create_node()));
            commands[1] = ft_lstlast(commands[0]);
        }
        commands[1]->content = ft_node(shell, commands[1]->content, temp, &index);
        if (index < 0)
            return (ft_exit_error(tokenize, commands[0], temp[0]));
        if (!tokenize[index])
            break;
    }
    ft_freetab(&temp[0]);
    ft_freetab(&tokenize);
    return (commands[0]);
}