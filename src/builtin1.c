#include "minishell.h"

int ft_is_valid_n_flag(char *cmd)
{
    int i;

    i = 1;
    if (!cmd)
        return (0);
    if (cmd[0] != '-' || cmd[1] != 'n')
        return (0);
    while (cmd[i] != '\0')
    {
        if (cmd[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

void	echo_shell(t_info *shell, t_commands commands, end)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (commands.commands[1] != NULL)
    {
        if (ft_is_valid_n_flag(commands.commands[i]) == 0 ||
            j == 1)
        {
            j = 1;
            i++;
        }
    }
}