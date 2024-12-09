/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:10:23 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/08 23:31:10 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 int ft_is_valid_env_var_format(char *str)
 {
    size_t index;

    index = 0;
    while (str[index] != '\0')
    {
        if (str[index] == '=')
            return (1);
        index++;
    }
    return (0);
 }

 void handle_env_exit(t_info *shell, char *commands, t_hashmap *cpy_env, int end)
 {
    free_hashmap(cpy_env);
    manage_exit(shell, commands, FILE_NOT_FOUND, end);
 }

void close_file_descriptors(t_info *shell, t_commands *commands)
{
    t_commands *temp;
    t_list *current;

    current = shell->commands;
    while (current != NULL)
    {
        temp = current->content;
        if (temp == commands)
        {
            current = current->next;
            continue;
        }
        if (temp->fd1 != 0)
            close(temp->fd1);
        if (temp->fd2 != 1)
            close(temp->fd2);
        current = current->next;
    }
}

char *ft_path(t_info *shell, char *commands)
{
    int index;
    char **path_directories;
    char *directory;
    char *full_path;

    index = 0;
    directory = cmds_in_hashmap(shell->env, "PATH");
    if (directory == NULL)
        return (NULL);
    path_directories = ft_split(directory + 5, ':');
    directory = NULL;
    full_path = NULL;
    while (path_directories[index])
    {
        directory = ft_strjoin(path_directories[index], "/");
        full_path = ft_strjoin(directory, commands);
        free(directory);
        if (access(full_path, F_OK) == 0)
            break;
        free(full_path);
        full_path = NULL;
        index++;
    }
    ft_freetab(&path_directories);
    return (full_path);
}

void ft_run_command(t_info *shell, t_commands *commands)
{
    char **temp;
    
    if (commands->command[0] == NULL)
        manage_exit(shell, NULL, 0, 1);
    handle_builtin_commands(shell, *commands, 1);
    commands->path = NULL;
    if (commands->command[0][0] != '/')
        commands->path = ft_path(shell, commands->command[0]);
    hashmap_in_tab(shell->env, &temp, 0, 0);
    if (commands->path == NULL)
        commands->path = ft_strdup(commands->command[0]);
    close_file_descriptors(shell, NULL);
    if (execve(commands->path, commands->command, temp) != 0)
    {
        free (commands->path);
        commands->path = NULL;
        if (opendir(commands->command[0]) != NULL)
            manage_exit(shell, commands->command[0], IS_A_DIRECTORY, 1);
        else if (commands->command[0][0] == '/')
            manage_exit(shell, commands->command[0], FILE_NOT_FOUND, 1);
        else
            manage_exit(shell, commands->command[0], COMMAND_NOT_FOUND, 1);           
    }
}