#include "minishell.h"

int ft_add_or_update_env(t_hashmap *env, char *str)
{
    char *key;
    char *value;
    int i;

    i = find_char_index(str, '=');
    if (i == 0 && str[i + 1] == '\0')
        i++;
    key = ft_substr(str, 0, i);
    value = ft_substr(str, ++i, ft_strlen(str));
    if (cmds_in_hashmap(env, key) != NULL)
    {
        if (delete_in_hashmap(env, key) == 1)
            return (1);
    }
    if (insertion_in_hashmap(key, value, env, 0) == NULL)
        return (1);
    free(key);
    free(value);
    return (0);
}