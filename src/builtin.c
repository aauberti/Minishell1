#include "minishell.h"

void exit_shell(t_info *shell, t_commands commands)
{
    int i;

    i = 1;
    if (commands.commands[1] != NULL && ft_isdigit(ft_atoi(commands.commands[1])) == 0)
    {
        manage_exit(shell, NULL, 0, 0);
        exit ((unsigned char)ft_atoi(commands.commands[1]));
    }
    else if (commands.commands[1] != NULL)
    {
        ft_putstr_fd("exit\n", 2);
        ft_putstr_fd("minishell: exit: ", 2);
        while (commands.commands[i] != NULL)
        {
            ft_putstr_fd(commands.commands[1], 2);
            ft_putstr_fd(" ", 2);
            i++;
        }
        ft_putstr_fd("invalid argument\n", 2);
    }
    else
        ft_putstr_fd("exit\n", 0);
    manage_exit(shell, NULL, 0, 1);
}

void pwd_shell(t_info *shell, t_commands commands, int end)
{
    char *pwd;

    pwd = cmd_in_hashmap(shell->env, "PWD");
    if (pwd == NULL)
    {
        manage_exit(shell, NULL, 1, end);
        return ;
    }
    ft_putstr_fd(pwd, commands.fd2);
    ft_putstr_fd("\n", commands.fd2);
    manage_exit(shell, NULL, 0, end);
}

void ft_printf_history(t_info *shell, int i)
{
    while (shell->history[i])
    {
        ft_printf(" %d: %s\n", i + 1, shell->history[i]);
        i++;
    }
}

int ft_isnumeric(char *cmd)
{
    int i;

    i = -1;
    while (cmd[++i])
    {
        if (!ft_isdigit(cmd[i]))
            return (0);
    }
    return (1);
}

void history_shell(t_info *shell, t_commands commands, int end)
{
    int size;
    int i;

    size = ft_tab_len(shell->history);
    i = 0;
    if (commands.commands[1] == NULL)
        ft_printf_history(shell, i);
    else if (!ft_isnumeric(commands.commands[1]))
    {
        manage_exit(shell, commands.commands[1], HISTORY_BAD_ARG, end);
        return ;
    }
    else if (commands.commands[1] && !commands.commands[2])
    {
        i = size - ft_atoi(commands.commands[1]);
        if (i < 0)
            i = 0;
        ft_printf_history(shell, i);
    }
    else if (commands.commands[1] && commands.commands[2])
    {
        manage_exit(shell, NULL, HISTORY_BAD_ARGS, end);
        return ;
    }
    manage_exit(shell, NULL, 0, end);
}