/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doliveira <doliveira@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:54:07 by dde-oliv          #+#    #+#             */
/*   Updated: 2021/06/29 17:10:00 by doliveira        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

void	ft_strrev(char **str)
{
	size_t		len_str;
	size_t		count;
	char		temp;

	len_str = ft_strlen(*str);
	if (len_str == 0)
		return ;
	len_str--;
	count = 0;
	while (count < len_str)
	{
		temp = (*str)[count];
		(*str)[count] = (*str)[len_str];
		(*str)[len_str] = temp;
		count++;
		len_str--;
	}
}
