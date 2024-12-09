/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_list2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:31 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/09 18:58:36 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands  *ft_create_node(void)
{
    t_commands  *new_node;

    new_node = malloc(sizeof(t_commands));
    if (!new_node)
        return (NULL);
    new_node->fd1 = 0;
    new_node->fd2 = 1;
    new_node->path = NULL;
    new_node->command = NULL;
    return (new_node);
}

void    free_command(void *content)
{
    t_commands  *node;

    node = content;
    ft_freetab(&node->command);
    free(node->command);
    if (node->fd1 != 0)
        close(node->fd1);
    if (node->fd2 != 1)
        close (node->fd2);
    free(node);
}

t_list  *ft_exit_error(char **tokenize, t_list *commands, char **temp)
{
    ft_lstclear(&commands, free_command);
    ft_freetab(&temp);
    ft_freetab(&tokenize);
    return (NULL);
}