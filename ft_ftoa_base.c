/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doliveira <doliveira@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:43:29 by doliveira         #+#    #+#             */
/*   Updated: 2021/06/30 18:02:44 by doliveira        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

static char	*get_ieee754 (double f)
{
	t_fbits	fnum;
	char	*fbits;
	int		size;
	int		count;

	fnum.f = f;
	size = sizeof (f) * 8;
	fbits = malloc(size + 1);
	if (!fbits)
		return (NULL);
	count = 0;
	while (size--)
	{
		fbits[count] = '0' + ((fnum.u >> size) & 1);
		count++;
	}
	fbits[count] = '\0';
	return (fbits);
}

static void	get_exceptions(double f, char **fstr)
{
	char	*fbits;
	char	*expoent;
	char	*mantissa;

	fbits = get_ieee754(f);
	expoent = ft_substr(fbits, 1, 11);
	mantissa = ft_substr(fbits, 12, 52);
	if (ft_strcmp(expoent, "11111111111") == 0 && ft_strcmp
		(mantissa, "0000000000000000000000000000000000000000000000000000") != 0)
		*fstr = strdup("nan");
	else if (fbits[0] == '0' && ft_strcmp(expoent, "11111111111") == 0)
		*fstr = strdup("inf");
	else if (ft_strcmp(expoent, "11111111111") == 0)
		*fstr = strdup("-inf");
	free(fbits);
	free(expoent);
	free(mantissa);
}

static void	get_round(char **fnum)
{
	char	*fnum_aux;
	size_t	fnum_len;

	fnum_len = ft_strlen(*fnum);
	while (fnum_len > 0 && (*fnum)[fnum_len - 1] == '9')
	{
		(*fnum)[fnum_len - 1] = '0';
		fnum_len--;
	}
	if (fnum_len == 0)
	{
		fnum_aux = *fnum;
		*fnum = ft_strjoin("1", *fnum);
		free(fnum_aux);
	}
	else
		(*fnum)[fnum_len - 1] = (*fnum)[fnum_len - 1] + 1;
}

static char	*get_strfloat(char **fnum, char *fpoint, int sig)
{
	char	*fpoint_aux;
	char	*fstr;
	char	*fstr_aux;

	fpoint_aux = fpoint;
	if (ft_strchr(fpoint, '.'))
	{
		get_round(fnum);
		fpoint = fpoint + 2;
	}
	fstr = ft_3strjoin(*fnum, ".", fpoint);
	free(*fnum);
	free(fpoint_aux);
	if (sig == -1)
	{
		fstr_aux = fstr;
		fstr = ft_strjoin("-", fstr);
		free(fstr_aux);
	}
	return (fstr);
}

char	*ft_ftoa_base(long double f, int n, char *base)
{
	char		*fnum;
	char		*fpoint;
	char		*fstr;
	int			sig;
	__int128_t	num;

	fstr = NULL;
	num = f;
	get_exceptions(f, &fstr);
	if (fstr)
		return (fstr);
	if (f < 0.0)
	{
		sig = -1;
		fnum = ft_u128toa_base(-num, base);
		fpoint = ft_upointtoa_base(-f + (double)num, base, n);
		if (n == 0 && *fpoint == '0' && num % 2 != 0 && -f + (double)num >= 0.5)
		{
			free(fpoint);
			fpoint = strdup ("1.0");
		}
	}
	else
	{
		sig = 1;
		fpoint = ft_upointtoa_base((f - (double)num), base, n);
		fnum = ft_u128toa_base(num, base);
		if (n == 0 && *fpoint == '0' && num % 2 != 0 && f - (double)num >= 0.5)
		{
			free(fpoint);
			fpoint = strdup ("1.0");
		}
	}

	fstr = get_strfloat (&fnum, fpoint, sig);
	return (fstr);
}
