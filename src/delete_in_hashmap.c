/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_in_hashmap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:10:15 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/07 19:10:16 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_and_nullify_item(t_hashmap *hashmap, t_hash_item *item, unsigned long int i)
{
    free_item_hashmap(item);
    hashmap->item[i] = NULL;
    hashmap->count--;
}

void replace_with_next_item(t_hashmap *hashmap, t_hash_item *item, unsigned long int i)
{
    hashmap->item[i] = item->next;
    free_item_hashmap(item);
    hashmap->count--;
}
void unlink_and_free_next_item(t_hashmap *hashmap, t_hash_item *item, char *key)
{
    t_hash_item *temp;
    
    while (item->next != NULL)
    {
        if (ft_strncmp(item->next->key, key, ft_strlen(key) + 1) == 0)
        {
            temp = item->next;
            item->next = item->next->next;
            free_item_hashmap(temp);
            hashmap->count--;
            return ;
        }
        item = item->next;
    }
}

int delete_in_hashmap(t_hashmap *hashmap, char *key)
{
    unsigned long int i;
    t_hash_item *current;

    if (!key)
        return (1);
    i = djb2_hash(key, hashmap->size);
    current = hashmap->item[i];
    if (current == NULL)
        remove_and_nullify_item(hashmap, current, i);
    else if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
        replace_with_next_item(hashmap, current, i);
    else
        unlink_and_free_next_item(hashmap, current, key);
    if (cmd_in_hashmap(hashmap, key))
        return (1);
    return (0);
}