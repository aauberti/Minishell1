/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:27:03 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/07 18:50:27 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_os(t_info *shell)
{
    char    *os;
    char    **temp;
    char    **env_tab;

    os = NULL;
    temp = NULL;
    env_tab = hashmap_in_tab(shell->env, &env_tab, 0, 0);
    execution(&temp, "uname", env_tab, "/usr/bin/uname");
    ft_freetab(&env_tab);
    if (!os)
        temp = ft_extend_tab(temp, "Linux");
    os = ft_strdup(temp[0]);
    ft_freetab(&temp);
    return (os);
}

char    *ft_user(t_info *shell)
{
    char    **env;
    char    *user;
    char    **user_info;

    user = NULL;
    user_info = NULL;
    env = hashmap_in_tab(shell->env, &env, 0, 0);
    execution(&user_info, "id -u", env, "/usr/bin/id");
    if (!user_info)
        user_info = ft_extend_tab(user_info, "-1");
    shell->uid = ft_atoi(user_info[0]);
    ft_freetab(&user_info);
    user_info = NULL;
    execution(&user_info, "whoami", env, "/usr/bin/whoami");
    ft_freetab(&env);
    if (!user_info)
        user_info = ft_extend_tab(user_info, "guest");
    user = ft_strdup(user_info[0]);
    ft_freetab(&user_info);
    return (user);
}

char    *ft_directory(t_info *shell)
{
    char    *temp;
    char    *home;
    char    *directory;

    directory = ft_strdup(cmds_in_hashmap(shell->env, "PWD"));
    if (!directory)
        directory = ft_strdup("/");
    home = cmds_in_hashmap(shell->env, "HOME");
    if (home && home[0] != '\0' && ft_strnstr(directory, home, ft_strlen(directory)))
    {
        temp = directory;
        directory = ft_strjoin("~", &temp[ft_strlen(home)]);
        free(temp);
    }
    return (directory);
}
char    *start_prompt(t_info *shell)
{
    char    *os;
    char    *prompt;
    char    *temp;

    os = ft_os(shell);
    prompt = ft_user(shell);
    temp = ft_strjoin_arg(3, os, prompt, "@shell");
    free(os);
    free(prompt);
    prompt = ft_directory(shell);
    os = ft_strjoin_arg(3, temp, prompt, "$>");
    free(prompt);
    free(temp);
    return (os);
}

char    *prompt(t_info *shell)
{
    char    *prmpt;
    char    *str;

    prmpt = start_prompt(shell);
    str = readline(prmpt);
    free(prmpt);
    if (!str)
    {
        printf("exit\n");
        return (NULL);
    }
    if (!str[0])
    {
        save_cmds_in_history(shell, str);
        add_history(str);
    }
    return (str);
}