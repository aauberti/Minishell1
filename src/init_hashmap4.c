#include "minishell.h"



t_hash_item *search_in_hashmap(t_hashmap *hashmap, char *key)
{
    unsigned long int i;
    t_hash_item *item;

    i = djb2_hash(key, hashmap->size);
    item = hashmap->items[i];
    while (item != NULL)
    {
        if (ft_strncmp(item->key, key, ft_strlen(key) + 1) == 0)
            return (item);
        item = item->next;
    }
    return (NULL);
}

void remove_env_var(t_info *shell, char *key)
{
    if (search_in_hashmap(shell->env, key) == NULL)
        return;
    if (delete_in_hashmap(shell->env, key) == 1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(key, 2);
        ft_putstr_fd("delete in hashmap failed\n", 2);
        return;
    }
}

