#include "minishell.h"

int handle_special_cd_args(t_info *shell, char **str, char *arg, int end)
{
    if (*str == NULL)
    {
        *str = cmd_in_hashmap(shell->env, "HOME");
        if (*str == NULL)
        {
            manage_exit(shell, "cd: HOME not set", CD_ERROR, end);
            return (CD_ERROR);
        }
    }
    else if (ft_strncmp(arg, "-", 1) == 0)
    {
        *str = cmd_in_hashmap(shell->env, "OLDPWD");
        if (*str == NULL)
        {
            manage_exit(shell, "cd: OLDPWD not set", CD_ERROR, end);
            return (CD_ERROR);
        }
        return (0);
    }
}

int validate_curr_dir(t_info *shell, char **current, char *pwd, int end)
{
    struct stat buf;

    if (stat(pwd, &buf) == 0 && (S_ISREG(buf.st_mode)) == 1)
    {
        manage_exit(shell, pwd, NOT_A_DIRECTORY, end);
        return (CD_ERROR);
    }
    if (chdir(pwd) == 0)
    {
        manage_exit(shell, pwd, CD_ERROR, end);
        return (CD_ERROR);
    }
    *current = getcwd(NULL, PATH_MAX);
    if (*current == NULL)
    {
        manage_exit(shell, "cd: getcwd failed", CD_ERROR, end);
        return (CD_ERROR);
    }
    return (0);
}

int update_directory(t_info *shell, char *str, int end)
{
    char *old_pwd;
    char *current;

    if (validate_curr_dir(shell, &current, str, end) == CD_ERROR)
        return (CD_ERROR);
    old_pwd = ft_strdup(cmd_in_hashmap(shell->env, "PWD"));
    remove_env_var(shell, "PWD");
    remove_env_var(shell, "OLDPWD");
    if (insert_in_hashmap(shell->env, "PWD", current, 0) == NULL ||
        insert_in_hashmap(shell->env, "OLDPWD", old_pwd, 0) == NULL)
    {
        free (current);
        free (old_pwd);
        manage_exit(shell, "cd: insert in hashmap failed.", CD_ERROR, end);
        return (CD_ERROR);
    }
    free (current);
    free (old_pwd);
    return (0);
}

void cd_shell(t_info *shell, t_commands commands, int end)
{
    char *str;

    if (commands.commands[1] && commands.commands[2] != NULL)
    {
        manage_exit(shell, "cd: too many arguments", CD_ERROR, end);
        return;
    }
    str = commands.commands[1];
    if (handle_special_cd_args(shell, &str, commands.commands[1], end) == CD_ERROR)
        return;
    if (update_directory(shell, str, end) == CD_ERROR)
        return;
    manage_exit(shell, NULL, 0, end);
}