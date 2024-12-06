/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:26:56 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/04 09:27:09 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}

static void	print_env(t_hash_item *env, int options)
{
	ft_putendl_fd("----------------------------", 1);
	ft_putstr_fd("| ", 1);
	if (options == 1)
		ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(env->key, 1);
	ft_putstr_fd(" | = | ", 1);
	if (env->value)
		ft_putstr_fd(env->value, 1);
	ft_putendl_fd(" |", 1);
}

void	hashmap_print_table(t_hashmap *table, int options)
{
	unsigned int	i;
	t_hash_item		*current;
	t_hash_item		*tmp;

	i = 0;
	while (i < table->size)
	{
		current = table->item[i];
		while (current != NULL)
		{
			tmp = current->next;
			print_env(current, options);
			current = tmp;
		}
		i++;
	}
	ft_putendl_fd("----------------------------", 1);
}
