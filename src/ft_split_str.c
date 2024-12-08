/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:22 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/08 12:31:40 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_word(char *str, char *sep, int nb[2])
{
    int     quote_state[2];

    quote_state[0] = 0;
    quote_state[1] = 0;
    while (str && str[nb[0]] != '\0')
    {
        if (!ft_strchr(sep, str[nb[0]]))
        {
            nb[1]++;
            while ((!ft_strchr(sep, str[nb[0]]) || quote_state[0]) && str[nb[0]])
            {
                if (!quote_state[1] && (str[nb[0]] == '\"' || str[nb[0]] == '\''))
                    quote_state[1] = str[nb[0]];
                quote_state[0] = (quote_state[0] + (str[nb[0]] == quote_state[1])) % 2;
                quote_state[1] *= quote_state[0] != 0;
                nb[0]++;
            }
            if (quote_state[0])
                return (-1);
        }
        else
            nb[0]++;
    }
    return (nb[1]);
}

char    **create_word(char **word, char *str, char *sep, int index[3])
{
    int     size;
    int     quote_state[2];

    quote_state[0] = 0;
    quote_state[1] = 0;
    size = ft_strlen(str);
    while (str[index[0]])
    {
        while (ft_strchr(sep, str[index[0]]) && str[index[0]] != '\0')
            index[0]++;
        index[1] = index [0];
        while ((!ft_strchr(sep, str[index[0]]) || quote_state[0] || quote_state[1]) && str[index[0]])
        {
            quote_state[0] = (quote_state[0] + (!quote_state[1] && str[index[0]] == '\'')) % 2;
            quote_state[1] = (quote_state[1] + (!quote_state[0] && str[index[0]] == '\"')) % 2;
            index[0]++;
        }
        if (index[1] >= size)
            word[index[2]++] = NULL;
        else
            word[index[2]++] = ft_substr(str, index[1], index[0] - index[1]);
    }
    return (word);
}
char    **ft_split_str(char *str, char *sep)
{
    char    **word;
    int     len;
    int     nb[2];
    int     index[3];

    if (!str)
        return (NULL);
    index[0] = 0;
    index[1] = 0;
    index[2] = 0;
    nb[0] = 0;
    nb[1] = 0;
    len = count_word(str, sep, nb);
    if (len ==  -1)
        return (NULL);
    word = ft_calloc(len + 1, sizeof(char *));
    if (!word)
        return (NULL);
    word = create_word(word, str, sep, index);
    return (word);
}