/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:50:52 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/08 15:01:02 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_fd_utils(char *path, int state[2], t_info *shell)
{
    struct stat file_stat;

    if (access(path, F_OK) == -1 && !state[0])
        manage_exit(shell, path, FILE_NOT_FOUND, 0);
    else if (!state[0] && access(path, R_OK) == -1)
        manage_exit(shell, path, NO_PERMISSION, 0);
    else if (state[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
        manage_exit(shell, path, NO_PERMISSION, 0);
    else if (state[0] && stat(path, &file_stat) == 0 && (S_ISDIR(file_stat.st_mode)) == 1)
        manage_exit(shell, path, IS_A_DIRECTORY, 0);
}

int ft_fd(int fd, char *path, int state[2], t_info *shell)
{
    int new_fd;

    if (fd > 2)
        close(fd);
    if (!path)
        return (-1);
    ft_fd_utils(path, state, shell);
    if (state[0] && state[1])
        new_fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0666);
    else if (state[0] && !state[1])
        new_fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0666);
    else if (!state[0] && fd != -1)
        new_fd = open(path, O_RDONLY);
    else
        new_fd = fd;
    return (new_fd);
}

t_commands *handle_output(t_commands *node, char **commands[2], int *i, t_info *shell)
{
    int state[2];

    state[0] = 1;
    state[1] = 0;
    (*i)++;
    if(commands[0][*i] && commands[1][*i] && (commands[1][*i][0] != '<' && commands[1][*i][0] != '>' && commands[1][*i][0] != '|'))
        node->fd2 = ft_fd(node->fd2, commands[0][*i], state, shell);
    if (node->fd2 == -1 || !commands[0][*i] || !commands[1][*i] || commands[1][*i][0] == '>' || commands[1][*i][0] == '<' || commands[1][*i][0] == '|')
    {
        if (commands[1][*i] && commands[1][*i][0] == '<')
            manage_exit(shell, "'<'", SYNTAX_ERROR, 0);
        else if (node->fd2 != -1 || (commands[1][*i] && commands[1][*i][0] == '|'))
            manage_exit(shell, "newline", SYNTAX_ERROR, 0);
        else 
            shell->exit_status = 1;
        *i = -1;
    }
    return (node);
}

t_commands *handle_output_append(t_commands *node, char **commands[2], int *i, t_info *shell)
{
    int state[2];

    state[0] = 1;
    state[1] = 1;
    (*i)++;
    if (commands[0][++(*i)] && commands[1][*i] && commands[1][*i][0] != '<' && commands[1][*i][0] != '>'
        && commands[1][*i][0] != '|')
        node->fd2 = ft_fd(node->fd2, commands[0][*i], state, shell);
    if (node->fd2 == -1 || !commands[0][*i] || !commands[1][*i] || commands[1][*i][0] == '>' 
        || commands[1][*i][0] == '<' || commands[1][*i][0] == '|')
    {
        if (commands[1][*i] && commands[1][*i + 1] && commands[1][*i][0] == '>' && commands[1][*i + 1][0] == '>')
            manage_exit(shell, "'>>'" , SYNTAX_ERROR, 0);
        else if (commands[1][*i] && commands[1][*i][0] == '>')
            manage_exit(shell, "'>'", SYNTAX_ERROR, 0);
        else if (commands[1][*i] && commands[1][*i][0] == '<')
            manage_exit(shell, "'<'", SYNTAX_ERROR, 0);
        else if (commands[1][*i] && commands[1][*i][0] == '|')
            manage_exit(shell, "'|'", SYNTAX_ERROR, 0);
        else if (node->fd2 == -1)
            manage_exit(shell, "'new_line'", SYNTAX_ERROR, 0);
        *i = -1;
    }
    return (node);
}

t_commands  *ft_node(t_info *shell, t_commands *node, char **commands[2], int *i)
{
    if (commands[1][*i] && !(*i == 1 && commands[1][*i - 1][0] == '|'))
    {
        if (commands[1][*i][0] == '>' && commands[1][*i + 1] && commands[1][*i + 1][0] == '>')
            node = handle_output_append(node, commands, i, shell);
        else if (commands[1][*i][0] == '>')
            node = handle_output(node, commands, i, shell);
        else if (commands[1][*i][0] == '<' && commands[1][*i + 1] && commands[1][*i + 1][0] == '<')
            node = configure_heredoc_input(node, commands, i, shell);
        else if (commands[1][*i][0] == '<')
            node = handle_input(node, commands, i, shell);
        else if (commands[1][*i][0] != '|' || (commands[1][*i][0] == '|' && commands[1][*i][1] == 0))
            node->command = insert_token(node->command, commands[0][*i], -1);
        else
            ft_node_error (commands, i, shell);
        return (node);
    }
    ft_node_error(commands, i, shell);
    return (node);
}

