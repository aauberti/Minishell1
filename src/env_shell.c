#include "minishell.h"

void detect_and_execute_command(t_info *shell, t_commands *commands)
{
    int index;
    char *str;

    index = 1;
    while (commands->commands[index] != NULL)
    {
        if (ft_is_valid_env_var_format(commands->commands[index]) == 1)
        {
            index++;
            continue;
        }
        str = ft_path(shell, commands->commands[index]);
        if (str == NULL)
            return;
        free(commands->commands[0]);
        commands->commands[0] = NULL;
        commands->commands = commands->commands + 1;
        ft_run_command(shell, commands);
        index++;
    }
}

t_hashmap *duplicate_env_hashmap(t_hashmap *hashmap)
{
    char **tab;
    t_hashmap *new;

    hashmap_to_tab(&tab, hashmap, 0, 0);
    new = init_hashmap(tab);
    ft_free_tab(&tab);
    return (new);
}

void free_hashmap(t_hashmap *hashmap)
{
    unsigned int index;
    t_hash_item *temp;
    t_hash_item *item;

    index = 0;
    while (index < hashmap->size)
    {
        item = hashmap->item[index];
        while (item != NULL)
        {
            temp = item->next;
            free_item_hashmap(item);
            item = temp;
        }
        index++;
    }
    free(hashmap->item);
    free(hashmap);
}

void env_shell(t_info *shell, t_commands commands, int end)
{
    t_hashmap *temp;
    int index;

    index = 1;
    temp = duplicate_env_hashmap(shell->env);
    if (!temp)
        return;
    detect_and_execute_command(shell, &commands);
    while (commands.commands[i] != NULL)
    {
        if (ft_is_valid_env_var_format(commands.commands[i]) == 0 ||
            ft_add_or_update_env(temp, commands.commands[i]) == 1)
        {
            handle_env_exit(shell, commands.commands[i], temp, end);
            return;
        }
        index++;
    }
    hashmap_print_table(temp, 2);
    free_hashmap(temp);
    manage_exit(shell, NULL, 0, end); 
}