/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebervas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:32:08 by ebervas           #+#    #+#             */
/*   Updated: 2024/10/10 09:54:34 by ebervas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_abs(int nbr)
{
	unsigned int	number;

	if (nbr < 0)
		number = -nbr;
	else
		number = nbr;
	return (number);
}

static char	*ft_reverse(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			tab[15];
	int				i;
	int				negatif;
	unsigned int	number;

	negatif = 0;
	i = 0;
	if (n == 0)
	{
		tab[0] = '0';
		tab[1] = '\0';
		return (ft_strdup(tab));
	}
	if (n < 0)
		negatif = 1;
	number = ft_abs(n);
	while (number)
	{
		tab[i++] = (number % 10) + '0';
		number /= 10;
	}
	if (negatif)
		tab[i++] = '-';
	tab[i] = '\0';
	return (ft_strdup(ft_reverse(tab)));
}