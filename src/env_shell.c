/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebervas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:10:19 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/08 11:06:47 by ebervas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void detect_and_execute_command(t_info *shell, t_commands *commands)
{
    int index;
    char *str;

    index = 1;
    while (commands->command[index] != NULL)
    {
        if (ft_is_valid_env_var_format(commands->command[index]) == 1)
        {
            index++;
            continue;
        }
        str = ft_path(shell, commands->command[index]);
        if (str == NULL)
            return;
        free(commands->command[0]);
        commands->command[0] = NULL;
        commands->command = commands->command + 1;
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
    while (commands.command[index] != NULL)
    {
        if (ft_is_valid_env_var_format(commands.command[index]) == 0 
            || ft_add_or_update_env(temp, commands.command[index]) == 1)
        {
            handle_env_exit(shell, commands.command[index], temp, end);
            return;
        }
        index++;
    }
    hashmap_print_table(temp, 2);
    free_hashmap(temp);
    manage_exit(shell, NULL, 0, end); 
}