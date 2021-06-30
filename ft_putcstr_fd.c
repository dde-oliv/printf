/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doliveira <doliveira@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 18:29:28 by doliveira         #+#    #+#             */
/*   Updated: 2021/06/30 10:52:42 by doliveira        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

char	*ft_putcstr_fd(char *s, char c, int fd, int *n)
{
	if (!s)
		return (NULL);
	while (*s && *s != c)
	{
		write(fd, s, 1);
		s++;
		(*n)++;
	}
	if (*s == c)
		s++;
	return (s);
}
