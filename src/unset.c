#include "minishell.h"


int process_unset_command(t_info *shell, t_commands command, int *status)
{
    while (command.command[++(status[0])] != NULL)
    {
        if (cmds_in_hashmap(shell->env, command.command[status[0]]) != NULL)
        {
            if (ft_is_valid_identifier(command.command[status[0]], -1, 0) == 0)
            {
                ft_putstr_fd("minishell: unset: ", 2);
                ft_putstr_fd(command.command[status[0]], 2);
                ft_putstr_fd("': not a valid identifier\n", 2);
                status[1] = 1;
            }
            else if (delete_in_hashmap(shell->env, command.command[status[0]]) != 0)
            {
                ft_putstr_fd("minishell: unset: '", 2);
                ft_putstr_fd(command.command[status[0]], 2);
                ft_putstr_fd("error deleting var\n", 2);
                status[1] = 1;
            }
        }
    }
    return (status[1]);
}

void unset_shell(t_info *shell, t_commands command, int end)
{
    int status[2];

    status[0] = -1;
    status[1] = 0;
    if (command.command[1] == NULL)
        manage_exit(shell, NULL, 0, end);
    process_unset_command(shell, command, status);
    manage_exit(shell, NULL, 0, end);    
}