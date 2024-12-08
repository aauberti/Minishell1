/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:11:04 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/07 19:11:05 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_heredoc_line(char *str[2], size_t size, char *end_heredoc, char *error)
{
    char *temp;
    
    str[0] = ft_calloc(sizeof(char), 1);
    str[1] = ft_calloc(sizeof(char), 1);
    while (shell_signal != SIGINT && (!str[0] || ft_strncmp(str[0], end_heredoc, size) 
        || ft_strlen(end_heredoc) != size))
    {
        temp = str[1];
        str[1] = ft_strjoin(str[1], str[0]);
        free(temp);
        free(str[0]);
        str[0] = readline("> ");
        if (!str[0])
        {
           ft_printf("%s (wanted %s)\n", error, end_heredoc);
           break;
        }
        temp = str[0];
        str[0] = ft_strjoin(str[0], "\n");
        free(temp);
        size = ft_strlen(str[0]) -1;
    }
    free(str[0]);
    return (str[1]);
}

int ft_heredoc_fd(char *end_heredoc, t_info *shell)
{
    char *error;
    char *str[2];
    int fd[2];

    str[0] = NULL;
    str[1] = NULL;
    shell->exit_status = 0;
    error = "Warning end of heredoc";
    if (pipe(fd) == -1)
    {
        manage_exit(shell, NULL, PIPE_ERROR, 0);
        return (-1);
    }
    str[1] = ft_heredoc_line(str, 0, end_heredoc, error);
    write(fd[1], str[1], ft_strlen(str[1]));
    free(str[1]);
    close(fd[1]);
    if (shell_signal == SIGINT)
    {
        close(fd[0]);
        return (-1);
    }
    return (fd[0]);
}

void ft_heredoc_error(char **commands, int *i, t_info *shell, t_commands *node)
{
    int size;

    size  = 0;
    while (commands[*i] && commands[*i][0] == '<')
    {
        (*i)++;
        size++;
    }
    if (size == 2)
        manage_exit(shell, "'<'", SYNTAX_ERROR, 0);
    else if (size == 3)
        manage_exit(shell, "'<<'", SYNTAX_ERROR, 0);
    else if (size == 4)
        manage_exit(shell, "'<<<'", SYNTAX_ERROR, 0);
    else if (commands[*i] && commands[*i][0] == '>')
        manage_exit(shell, "'>'", SYNTAX_ERROR, 0);
    else if (commands[*i] && commands[*i][0] == '|')
        manage_exit(shell, "'|'", SYNTAX_ERROR, 0);
    else if (node->fd1 != -1 || size == 1)
        manage_exit(shell, "'newline'", SYNTAX_ERROR, 0);
    else
        shell->exit_status = 1;
}

t_commands *configure_heredoc_input(t_commands *node, char **commands[2], int *i, t_info *shell)
{
    char *end_heredoc;

    end_heredoc = NULL;
    (*i)++;
    if (commands[0][++(*i)] && commands[1][*i][0] != '<' && commands[1][*i][0] != '>'
        && commands[1][*i][0] != '|')
    {
        end_heredoc = (commands[0][*i]);
        node->fd1 = ft_heredoc_fd(end_heredoc, shell);
    }
    if (!commands[0][*i] || node->fd1 == -1 || commands[1][*i][0] == '<' || commands[1][*i][0] == '>'
        || commands[1][*i][0] == '|')
    {
        ft_heredoc_error(commands[1], i, shell, node);
        *i = -1;
    }
    return (node);
}