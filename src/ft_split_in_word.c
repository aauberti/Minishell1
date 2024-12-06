/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_in_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:19 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/04 09:27:17 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_in_word(char *str, char *sep, int nb)
{
    int     state[2];
    int     index;

    index = 0;
    state[0] = 0;
    state[1] = 0;
    while (str && str[index] != '\0')
    {
        nb++;
        if (!ft_strchr(sep, str[index]))
        {
            while ((!ft_strchr(sep, str[index]) || state[0] || state[1]) && str[index] != '\0')
            {
                state[0] = (state[0] + (!state[1] && str[index] == '\'')) % 2;
                state[1] = (state[1] + (!state[0] && str[index] == '\"')) % 2;
                index++;
            }
            if (state[0] || state[1])
                return (-1);
        }
        else
            index++;
    }
    return (nb);
}

char    **ft_create_in_word(char **word, char *str, char *sep, int index[3])
{
    int     state[2];

    state[0] = 0;
    state[1] = 0;

    while (str && str[index[0]] != '\0')
    {
        index[1] = index[0];
        if (!ft_strchr(sep, str[index[0]]))
        {
            while ((!ft_strchr(sep, str[index[0]]) || state[0] || state[1]) && str[index[0]])
            {
                state[0] = (state[0] + (!state[1] && str[index[0]] == '\'')) % 2;
                state[1] = (state[1] + (!state[0] && str[index[0]] == '\"')) % 2;
                index[0]++;
            }
        }
        else
            index[0]++;
        word [index[2]++] = ft_substr(str, index[1], index[0] - index[1]);
    }
    return (word);
}
char    **ft_split_in_word(const char *str, char *sep)
{
    int     size;
    int     i[3];
    char    **word;

    if (!str)
        return (NULL);
    i[0] = 0;
    i[1] = 0;
    i[2] = 0;
    size = count_in_word((char *)str, sep, 0);
    if (size == -1)
        return (NULL);
    word == malloc((size + 1) * sizeof(char *));
    if (!word)
        return (NULL);
    word = ft_create_in_word(word, (char *)str, sep, i);
    word[size] = NULL;
    return (word);
}

char    **insert_in_word(char ***word, char **new_word, int index)
{
    char    **temp;
    int     i[3];

    i[0] = -1;
    i[1] = -1;
    i[2] = -1;
    if(!word || !*word || index < 0 || index >= ft_tab_len(*word))
        return (NULL);
    temp = ft_calloc(ft_tab_len(*word) + ft_tab_len(new_word), sizeof(char *));
    while (temp && word[0][++i[0]])
    {
        if (i[0] != index)
            temp[++i[1]] = ft_strdup(word[0][i[0]]);
        else
        {
            while (new_word && new_word[++i[2]])
                temp[++i[1]] = ft_strdup(new_word[i[2]]);
        }
    }
    ft_freetab(word);
    *word = temp;
    return (*word);
}