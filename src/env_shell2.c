#include "minishell.h"

char *ft_path(t_info *shell, char *commands)
{
    int index;
    char **path_directories;
    char *directory;
    char *full_path

    index = 0;
    directory = cmd_in_hashmap(shell->env, "PATH");
    if (directory == NULL)
        return (NULL);
    path_directories = ft_split(directory + 5, ':');
    directory = NULL;
    full_path = NULL;
    while (path_directories[index])
    {
        directory = ft_strjoin("/", commands);
        full_path = ft_strjoin(path_directories[index], directory);
        free(directory);
        if (access(full_path, F_OK) == 0)
            break;
        free(full_path);
        full_path = NULL;
        index++;
    }
    ft_free_tab(&path_directories);
    return (full_path);
}

void ft_run_command(t_info *shell, t_commands *commands)
{
    char **temp;
    
    if (commands->commands[0] == NULL)
        manage_exit(shell, NULL, 0, 1);
    handle_builtin_commands(shell, *commands, 1);
    commands->path = NULL;
    if (commands->commands[0][0] != '/')
        commands->path = ft_path(shell, commands->commands[0]);
    hashmap_to_tab(shell->env, &temp, 0, 0);
    if (commands->path == NULL)
        commands->path = ft_strdup(commands->commands[0]);
    close_file_descriptors(shell, NULL);
    if (execve(commands->path, commands->commands, temp) != 0)
    {
        free (commands->path);
        commands->path = NULL;
        if (opendir(commands->commands[0]) != NULL)
            manage_exit(shell, commands->commands[0], IS_A_DIRECTORY, 1);
        else if (commands->commands[0][0] == '/')
            manage_exit(shell, commands->commands[0], FILE_NOT_FOUND, 1);
        else
            manage_exit(shell, commands->commands[0], COMMAND_NOT_FOUND, 1);           
    }
}