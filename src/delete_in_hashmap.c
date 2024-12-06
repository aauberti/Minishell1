#include "minishell.h"

void remove_end_nullify_item(t_hashmap *hashmap, t_hash_item *item, unsigned long int i)
{
    free_item_hashmap(item);
    hashmap->items[i] = NULL;
    hashmap->count--;
}

void replace_with_next_item(t_hashmap *hashmap, t_hash_item *item, unsigned long int i)
{
    hashmap->items[i] = item->next;
    free_item_hashmap(item);
    hashmap->count--;
}
void unlink_end_free_next_item(t_hashmap *hashmap, t_hash_item *item, char *key)
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