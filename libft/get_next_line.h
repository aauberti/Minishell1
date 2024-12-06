/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauberti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:37:58 by aauberti          #+#    #+#             */
/*   Updated: 2024/10/12 13:39:21 by aauberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

void	*ft_memcpy_gnl(void *dest, const void *src, size_t n);
char	*ft_strdup_gnl(const char *s);
char	*ft_strchr_gnl(char *s, int c);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*ft_read_line(int fd, char *str);
char	*ft_line(char *str);
char	*ft_rest(char *str);
char	*get_next_line(int fd);
int		ft_read_data(int fd, char **str);

#endif
