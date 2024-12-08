/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:10:34 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/08 12:55:18 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void extract_key_value(char **var, char **key, char **value, int *count)
{
    if (ft_strchr(var[count[0]], '=') == NULL)
    {
        *key = ft_strdup(var[count[0]]);
        *value = ft_strdup("");
    }
    else
    {
        count[1] = find_char_index(var[count[0]], '=');
        *key = ft_substr(var[count[0]], 0, count[1]);
        if (count[1] == -1)
            *value = ft_strdup("");
        else
            *value = ft_substr(var[count[0]], ++count[1], ft_strlen(var[count[0]]));
    }
}

int insert_custom_variables(t_info *shell, char **var, int *count)
{
    char *key;
    int flag;
    char *value;

    while (var[count[0]] != NULL && count[2] == 1)
    {
        extract_key_value(var, &key, &value, count);
        if (ft_is_valid_identifier(key, -1, 1) == 0)
        {
            count[0]++;
            continue ;
        }
        flag = fetch_hashmap_flag(shell->env, key);
        remove_env_var(shell, key);
        count[2] = (insertion_in_hashmap(shell->env, key, value, flag) != NULL);
        free(key);
        free(value);
        count[0]++;
    }
    return (count[2]);
}

int ft_is_valid_identifier(char *key, int i, int expect_alpha)
{
    if (key[0] == '\0' || key[0] == '=')
        return (0);
    if (expect_alpha == 1)
    {
        while (key[++i] != '\0')
        {
            if (ft_isalpha(key[i]) == 0)
                return (0);
            else
                break;
        }
    }
    i = -1;
    while (key[++i] != '\0' && key[i] != '=')
    {
        if (ft_isalnum(key[i]) == 0 && key[i] != '=')
            return (0);
        if (key[i] == '=' && ft_isalnum(key[i - 1]) == 0 && key[i + 1] != '\0')
            return (0);
    }
    return (1);
}

int process_export(t_info *shell, t_commands commands, int *count)
{
    int res;
    int i;
    
    i = 1;
    res = 0;
    while (commands.command[i] != NULL)
    {
        if (ft_is_valid_identifier(commands.command[i], -1, 1) == 0)
        {
            ft_putstr_fd("minishell: export: ", 2);
            ft_putstr_fd(commands.command[i], 2);
            ft_putstr_fd(": not a valid identifier\n", 2);
            res = 1;
        }
        else 
        {
            if (insert_custom_variables(shell, commands.command, count) == 0)
                res = HASH_TABLE_FULL;
        }
        i++;
    }
    return (res);
}

void export_shell(t_info *shell, t_commands commands, int end)
{
    int count[3];
    int res;

    if (commands.command[1] == NULL)
    {
        hashmap_print_table(shell->env, 1);
        manage_exit(shell, NULL, 0, end);
        return ;
    }
    count[0] = 1;
    count[1] = 0;
    count[2] = 1;
    res = process_export(shell, commands, count);
    manage_exit(shell, NULL, res, end);
}