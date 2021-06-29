/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dpointtoa_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doliveira <doliveira@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:48:34 by doliveira         #+#    #+#             */
/*   Updated: 2021/06/28 17:30:36 by doliveira        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

static void	get_round(char **str, size_t str_len)
{
	char	*str_aux;

	str_aux = *str;
	*str = ft_strcjoin(*str, '0');
	free(str_aux);
	while (str_len > 0 && (*str)[str_len - 1] == '9')
	{
		(*str)[str_len - 1] = '0';
		str_len--;
	}
	if (str_len == 0)
	{
		str_aux = *str;
		*str = ft_strjoin("1.", *str);
		free(str_aux);
	}
	else
		(*str)[str_len - 1] = (*str)[str_len - 1] + 1;
}

static void	get_lastdigit(double f, char *base, size_t base_size, char **str)
{
	char	ldigit;
	char	*str_aux;
	size_t	str_len;

	str_len = ft_strlen(*str);
	ldigit = base[(int64_t)(f * 10) % base_size];
	f = f * 10 - (int64_t)(f * 10.0);
	if (f * 10 <= 5.0 || ldigit != '9')
	{
		str_aux = *str;
		if (f * 10 <= 5.0)
			*str = ft_strcjoin(*str, ldigit);
		else if (ldigit != '9')
			*str = ft_strcjoin(*str, ldigit + 1);
		free(str_aux);
	}
	else
		get_round(str, str_len);
}

static char	*get_exceptions(double f, char *base, size_t precision, size_t size)
{
	char	*str;

	size = ft_strlen(base);
	if (f == 0)
	{
		str = ft_strcjoin("", base[0]);
		return (str);
	}
	if (precision == 0)
	{
		if (base[(int)(f * 10) % size] < '5')
			str = ft_strdup("0");
		else
			str = ft_strdup("1.0");
		return (str);
	}
	return (NULL);
}

char	*ft_dpointtoa_base(double f, char *base, size_t precision)
{
	size_t			size;
	char			*str;
	char			*str_aux;
	size_t			count;

	size = ft_strlen(base);
	str = get_exceptions(f, base, precision, size);
	if (str)
		return (str);
	str = ft_calloc(1, sizeof(char));
	count = 0;
	while (f != 0 && count + 1 < precision)
	{
		str_aux = str;
		str = ft_strcjoin(str, base[(int64_t)(f * 10) % size]);
		free(str_aux);
		f = f * 10 - (int64_t)(f * 10.0);
		count++;
	}
	get_lastdigit(f, base, size, &str);
	return (str);
}
