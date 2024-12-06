/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:59 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/04 09:27:08 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

void	ft_freetab(char ***tab)
{
	int	i;

	i = 0;
	while (tab && tab[0] && tab[0][i])
	{
		free(tab[0][i]);
		i++;
	}
	if (tab && *tab)
	{
		free(*tab);
		*tab = NULL;
	}
}

char	**ft_extend_tab(char **tab, char *str)
{
	char	**new;
	int		len;
	int		i;

	i = -1;
	new = NULL;
	if (!str)
		return (tab);
	len = ft_tab_len(tab);
	new = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (NULL);
	new[len + 1] = NULL;
	while (++i < len)
	{
		new[i] = ft_strdup(tab[i]);
		if (!new[i])
		{
			ft_freetab(&tab);
			ft_freetab(&new);
		}
	}
	new[i] = ft_strdup(str);
	ft_freetab(&tab);
	return (new);
}

char	*ft_strjoin_arg(unsigned int size, ...)
{
	unsigned int i;
	char	*temp;
	char	*join;
	char	*arg_temp;
	va_list	list;

	va_start(list, size);
	i = 0;
	join = NULL;
	while (i < size)
	{
		arg_temp = va_arg(list, char *);
		if (join == NULL)
			join = ft_strdup(arg_temp);
		else
		{
			temp = ft_strjoin(join, arg_temp);
			free(join);
			join = temp;
		}
		i++;
	}
	va_end(list);
	return (join);
}

void    save_cmds_in_history(t_info *shell, char *cmd)
{
    char    *history;

    history = ft_strdup(cmd);
    if (!history)
        return ;
    shell->history = ft_extend_tab(shell->history, cmd);
    free(cmd);
}