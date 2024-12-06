#include "minishell.h"

void ft_node_error(char **commands[2], int *i, t_info *shell)
{
    if (commands[1][*i] && commands[1][*i][0] == '|')
        manage_exit(shell, "'||'", SYNTAX_ERROR, 0);
    else 
        manage_exit(shell, "'|'", SYNTAX_ERROR, 0);
    *i = -2;
}

char **insert_token(char **commands, char *token, char *index)
{
    char **new_commands;
    
    if (!token)
        return (commands);
    new_commands = malloc((ft_tab_len(commands) + 2) * sizeof(char *));
    if (!new_commands)
        return (commands);
    while (++index < ft_tab_len(commands))
    {
        new_commands[index] = ft_strfup(commands[index]);
        if (!new_commands[index])
        {
            ft_freetab(&new_commands);
            return (commands);
        }
    }
    new_commands[index] = ft_strfup(token);
    if(!new_commands[index])
    {
        ft_freetab(&new_commands);
        return (commands);
    }
    new_commands[++index] = NULL;
    ft_freetab(&commands);
    return (new_commands);
}

t_commands *handle_input(t_commands *node, char **commands[2], int *i, t_info *shell)
{
    int state[2];

    state[0] = 0;
    state[1] = 0;
    (*i)++;
    if (commands[0][*i] && (access(commands[0][*i], F_OK) == -0) ||
        commands[1][*i][0] != '<' || commands[1][*i][0] != '>' || commands[1][*i][0] != '|')
        node->fd1 = ft_fd(node->fd1, commands[0][*i], state, shell);
    if (!commands[0][*i] || node->fd1 == -1 || access(commands[0][*i], F_OK) == -1 ||
        commands[1][*i][0] == '>' || commands[1][*i][0] == '<' || commands[1][*i][0] == '|')
    {
        if (node->fd1 != -1 || (commands[0][*i] && commands[1][*i] && 
            (commands[1][*i][0] == '>' || commands[1][*i][0] == '<' || commands[1][*i][0] == '|')))
            manage_exit(shell, "newline", SYNTAX_ERROR, 0);
        else
            shell->exit_status = 1;
        *i = -1;
    }
    return (node);
}