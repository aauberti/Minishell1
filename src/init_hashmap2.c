/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hashmap2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:39 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/08 12:06:16 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long int   djb2_hash(char *key, unsigned int size)
{
    unsigned long int   hash_value;
    unsigned int        i;

    hash_value = 5381;
    i = 0;
    while (key && key[i])
    {
        hash_value = ((hash_value << 5) + hash_value) + key[i];
        i++;
    }
    return (hash_value % size);
    
}

t_hash_item     *new_hashmap_item(char *key, char *value, int status)
{
    t_hash_item *new_item;

    new_item = (t_hash_item *)ft_calloc(sizeof(t_hash_item), 1);
    if(!new_item)
        return(NULL);
    new_item->key = ft_strdup(key);
    new_item->value = ft_strdup(value);
    new_item->status = status;
    new_item->next = NULL;
    return (new_item);
}

void    free_item_hashmap(t_hash_item *item)
{
    free(item->key);
    free(item->value);
    free(item);
}

int new_item_in_hashmap(int i, t_hashmap *table, t_hash_item *new_item)
{
    if (table->count == table->size)
    {
        manage_exit(NULL, NULL, HASH_TABLE_FULL, 0);
        free_item_hashmap(new_item);
        return (0);
    }
    table->item[i] = new_item;
    table->count++;
    return (1);
}
t_hash_item     *insertion_in_hashmap(t_hashmap *table, char *key, char *value, int status)
{
    unsigned long int   i;
    t_hash_item *new_item;
    t_hash_item *current_item;

    if (!key)
        return (NULL);
    i = djb2_hash(key, table->size);
    new_item = new_hashmap_item(key, value, status);
    current_item = table->item[i];
    if (current_item == NULL)
    {
        if(!new_item_in_hashmap(i, table, new_item))
            return (NULL);
    }
    else
    {
        if (ft_strncmp(current_item->key, key, ft_strlen(key) + 1) == 0)
            hashmap_replace_value(status, current_item, value, new_item);
        else
           hashmap_collisison(status, table, i, new_item);
    }
    return (new_item);
}