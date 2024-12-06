/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebervas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:41:21 by ebervas           #+#    #+#             */
/*   Updated: 2024/10/23 10:29:09 by ebervas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_search_hexadecimal(unsigned int num, const char word)
{
	if (num >= 16)
	{
		ft_search_hexadecimal(num / 16, word);
		ft_search_hexadecimal(num % 16, word);
	}
	else
	{
		if (num < 10)
			ft_print_character(num + '0');
		else
		{
			if (word == 'x')
				ft_print_character(num - 10 + 'a');
			if (word == 'X')
				ft_print_character(num - 10 + 'A');
		}
	}
}

static int	ft_length_hexadecimal(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

int	ft_print_hexadecimal(unsigned int num, const char word)
{
	if (num == 0)
		return (ft_print_character('0'));
	else
		ft_search_hexadecimal(num, word);
	return (ft_length_hexadecimal(num));
}
