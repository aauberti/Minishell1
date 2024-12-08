/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_shell2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:10:38 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/07 19:10:39 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_char_index(char *str, char c)
{
    int index;

    index = 0;
    if (!str)
        return (-1);
    while (str[index] != '\0')
    {
        if (str[index] == c)
            return (index);
        index++;
    }
    return (-1);
}

int fetch_hashmap_flag(t_hashmap *hashmap, char * key)
{
    unsigned long int i;
    t_hash_item *item;

    i = djb2_hash(key, hashmap->size);
    item = hashmap->item[i];
    while (item != NULL)
    {
        if (ft_strncmp(item->key, key, ft_strlen(key) + 1) == 0)
            return (item->status);
        item = item->next;
    }
    return (1);
}