/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hashmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:35 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/04 09:27:14 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *extract_key(char *line)
{
    char    *key;
    int     i;

    i = 0;
    while (line[i] != '=' && line[i] != '\0')
        i++;
    key = ft_substr(line, 0, i);
    return (key);
}

char    *extract_value(char *line)
{
    char    *value;
    int     i;
    int     j;

    i = 0;
    while (line[i] != '=' && line[i] != '\0')
        i++;
    i++;
    j = i;
    while (line[j] != '\0')
        j++;
    value = ft_substr(line, i, j);
    return (value);
}
t_hashmap   *creating_table(unsigned int size)
{
    t_hashmap   *table;
    unsigned int         i;

    i = 0;
    table = (t_hashmap *)ft_calloc(sizeof(t_hashmap), 1);
    if(!table)
        return (NULL);
    table->count = 0;
    table->size = size;
    table->item = (t_hash_item **)ft_calloc(sizeof(t_hash_item *), size);
    if(!table->item)
    {
        free(table);
        return (NULL);
    }
    while (i < size)
    {
        table->item[i] = NULL;
        i++;
    }
    return (table);
}

t_hashmap   *init_hashmap(char  **envp)
{
    t_hashmap   *table;
    int         len;
    char        *key;
    char        *value;
    int         i;
    
    len = 0;
    i = -1;
    while(envp[len])
        len++;
    if(len)
        table = creating_table(len * 2);
    else
        table = creating_table(100);
    if(!table)
        exit(1);  
    while (++i < len)
    {
        key = extract_key(envp[i]);
        value = extract_value(envp[i]);
        insertion_in_hashmap(table, key, value, 0);
        free(key);
        free(value);
    }
    return (table);
}