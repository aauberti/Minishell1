/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:04 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/04 09:27:20 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    end_execution(char ***tab, int fd)
{
    char    **temp;
    char    *line;
    char    *trim_line;

    temp = NULL;
    line = NULL;
    trim_line = NULL;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        trim_line = ft_strtrim(line, "\n");
        free(line);
        temp = ft_extend_tab(temp, trim_line);
        free(trim_line);
    }
    ft_freetab(tab);
    *tab = temp;
}

void    execution(char  ***tab, char *command, char **env, char *path)
{
    pid_t   pid;
    char    **temp;
    int     fd[2];

    pipe(fd);
    pid = fork();
    if (!pid)
    {
        close(fd[0]);
        temp = ft_split(command, ' ');
        dup2(fd[1], 1);
        close(fd[1]);
        if (access(path, F_OK) == 0)
            execve(path, temp, env);
        exit(1);
    }
    close(fd[1]);
    waitpid(pid, NULL, 0);
    end_execution(tab, fd[0]);
    close(fd[0]);
}