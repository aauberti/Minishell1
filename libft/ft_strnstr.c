/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebervas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:20:32 by ebervas           #+#    #+#             */
/*   Updated: 2024/10/09 17:07:16 by ebervas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	comp;
	size_t	len_lit;

	if (!little[0])
		return ((char *)big);
	if (len == 0)
		return (NULL);
	len_lit = ft_strlen(little);
	comp = 1;
	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (*big && i < len)
	{
		if (*big == little[0] && (len_lit + i) <= len)
			comp = ft_strncmp(big, little, len_lit);
		if (comp == 0)
			return ((char *)big);
		big++;
		i++;
	}
	return (NULL);
}
