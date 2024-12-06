/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hashmap3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:42 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/04 09:27:11 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void hashmap_replace_value(int status, t_hash_item *current_item, char *value, t_hash_item *new_item)
{
    free(current_item->value);
    current_item->value = NULL;
    current_item->value = ft_strdup(value);
    current_item->status = status;
    free_item_hashmap(new_item);
}

void    hashmap_collisison(int status, t_hashmap *table,unsigned long int i, t_hash_item *new_item)
{
    t_hash_item *current_item;

    current_item = table->item[i];
    while (current_item->next != NULL)
        current_item = current_item->next;
    current_item->next = new_item;
    current_item->next->status = status;
    current_item->next->next = NULL;
    table->count++;
}

char    *cmds_in_hashmap(t_hashmap *table, char *key)
{
    unsigned long int   i;
    t_hash_item *current;
    
    i = djb2_hash(key, table->size);
    current = table->item[i];
    while (current != NULL)
    {
        if (ft_strncmp(current->key, key,ft_strlen(key) + 1) == 0)
            return (current->value);
        current = current->next;
    }
    return (NULL);
}

char	*ft_strjoin_3(char const *s1, char const *s2)
{
	size_t	len;
	int		i;
	int		j;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (NULL);
	while (s1[++i])
		new_str[i] = s1[i];
    new_str[i++] = '=';
	while (s2[j])
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char    **hashmap_in_tab(t_hashmap *env_tab, char ***tab, unsigned int i, unsigned int j)
{
    char    *str;
    t_hash_item *current;
    t_hash_item *temp;

    *tab = ft_calloc(env_tab->count + 1, sizeof(char *));
    if(!*tab)
        return (NULL);
    while (i < env_tab->size)
    {
        current = env_tab->item[i];
        while (current != NULL)
        {
            temp = current->next;
            str = ft_strjoin_3(current->key, current->value);
            (*tab)[j] = str;
            current = temp;
            j++;
        }
        i++;
    }
    return (*tab);
}
