/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:12 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/09 11:41:14 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_in_charset(const char *str, char *charset)
{
    int     index;

    index = -1;
    if(!str)
        return (index);
    while(str[++index])
    {
        if (ft_strchr(charset, str[index]))
            return (index);
    }
    return (-1);
}

char    *ft_in_var2(char *token, int index, t_info *shell, char *temp)
{
    char    *var;

    if (token[index] == '$')
        var = ft_itoa((int)shell->pid);
    else if (token[index] == '?')
        var = ft_itoa(shell->exit_status);
    else if (ft_strncmp(temp, "UID", 4) == 0)
        var = ft_itoa(shell->uid);
    else
        var = ft_strdup(cmds_in_hashmap(shell->env, temp));
    if (!var && (token[index] == '\'' || token[index] == '\"'))
        var = ft_strdup(temp);
    else if (!var && ft_in_charset(&token[index], "!@#%^&|\"\'$?<> ") == -1 && index > 0 && ft_strchr("=", token[index - 1]))
        var = NULL;
    else if (!var)
        var = ft_strdup("");
    return (var);
}
char    *ft_in_var(char *token, int index, t_info *shell)
{
    char    *var;
    char    *temp;
    char    *loc;
    int     state;

    state = ft_in_charset(&token[index], "=!@#%^&|\"\'$?<> ") + (ft_strchr("$?", token[index]) != 0);
    if (!state && (token[index] == '\'' || token[index] == '\"'))
        state += ft_in_charset(&token[index + 1], "\"\'") + 1;
    if (state == -1)
        state = ft_strlen(token) - 1;
    temp = ft_substr(token, index, state);
    var = ft_in_var2(token, index, shell, temp);
    free(temp);
    temp = ft_substr(token, 0, index - 1);
    loc = ft_strjoin(temp, var);
    free(temp);
    free(var);
    temp = ft_strjoin(loc, &token[index + state]);
    free(loc);
    free(token);
    return (temp);
}

char    *handle_variable_expand(t_info *shell, char *token, int state[2], int index)
{
    state[0] = 0;
    state[1] = 0;
    while(token && token[++index])
    {
        state[0] = (state[0] + (!state[1] && token[index] == '\'')) % 2; 
        state[1] = (state[1] + (!state[0] && token[index] == '\"')) % 2; 
        if (!state[0] && token[index] == '$' && token[index + 1] && ((!state[1] && ft_in_charset(&token[index + 1], "=/~%^{}:; ")) || (state[1] && ft_in_charset(&token[index + 1], "=/~%^{}:;\'\" "))))
            return (handle_variable_expand(shell,ft_in_var(token, ++index, shell), state, -1));  
    }
    return (token);   
}

void    ft_expand(t_info *shell, char **tokenize)
{
    int tab_len;
    int state[2];
    int index;

    tab_len = ft_tab_len(tokenize);
    index = 0;
    while (tokenize && tokenize[index])
    {
        if (index > 1 && (tokenize[index - 1] && tokenize[index - 2]) && tokenize[index -1][0] == '<' && tokenize[index - 2][0] == '<')
        {
            index++;
            continue ;
        }
        tokenize[index] = handle_variable_expand(shell, tokenize[index], state, -1);
        tokenize[index] = handle_variable_home(tokenize[index], -1, state, ft_strdup(cmds_in_hashmap(shell->env, "HOME")));
        if (!tokenize[index])
            update_tab(tokenize, index, tab_len);
        else
            index++;
    }
}