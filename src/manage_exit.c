/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:09:32 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/07 18:49:44 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_close(t_info *shell, t_commands *command)
{
    t_commands *node;
    t_list *current;

    current = shell->commands;
    while (current != NULL)
    {
        node = current->content;
        if (node->command)
        {
            current = current->next;
            continue;
        }
        if (node->fd1 != 0)
            close(node->fd1);
        if (node->fd2 != 1)
            close(node->fd2);
        current = current->next;
    }
}

void ft_free_item(t_hash_item *item)
{
    free(item->key);
    free(item->value);
    free(item);
}

void ft_free_hashmap(t_hashmap *hashmap)
{
    t_hash_item *item;
    t_hash_item *temp;
    unsigned int index;

    index = 0;
    while (index < hashmap->size)
    {
        item = hashmap->item[index];
        while (item != NULL)
        {
            temp = item->next;
            ft_free_item(item);
            item = temp;
        }
        index++;
    }
    free(hashmap->item);
    free(hashmap);
}

void ft_exit_all(t_info *shell)
{
    if (shell)
    {
        if (shell->env)
            ft_free_hashmap(shell->env);
        if (shell->commands)
            ft_lstclear(&shell->commands, free_command);
        if (shell->pids)
            free(shell->pids);
    }
    exit(shell->exit_status);
}

void    manage_exit(t_info *shell, char *arguments, int error, int end)
{
    if (error == FORK_ERROR || error == PIPE_ERROR || error == HISTORY_BAD_ARG || error == HISTORY_BAD_ARGS || error == CD_ERROR || error == NOT_A_DIRECTORY)
        shell->exit_status = 1;
    else if (error == SYNTAX_ERROR)
        shell->exit_status = 2;
    else if (error == COMMAND_NOT_FOUND)
        shell->exit_status = 127;
    else if (error = IS_A_DIRECTORY)
        shell->exit_status = 126;
    else
        shell->exit_status = error;
    if (error != SUCCESS && error != FAILURE && error != ERROR)
        ft_print_error(arguments, error);
    if (shell && shell->commands)
        ft_close(shell, NULL);
    if (end)
        ft_exit_all(shell);
}
