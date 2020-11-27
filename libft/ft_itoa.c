/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 03:03:01 by vicmarti          #+#    #+#             */
/*   Updated: 2020/01/21 21:24:08 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	numl(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void		wdigits(char *dst, unsigned int n, size_t ndgts)
{
	while (ndgts > 0)
	{
		dst[--ndgts] = (n % 10) + '0';
		n /= 10;
	}
}

char			*ft_itoa(int n)
{
	char	*numstr;
	size_t	i;

	i = numl(n);
	if (NULL == (numstr = malloc(i + 1)))
		return (numstr);
	numstr[i] = 0;
	if (n < 0)
	{
		*numstr = '-';
		wdigits(numstr + 1, (unsigned int)(-1 * n), i - 1);
	}
	else
		wdigits(numstr, (unsigned int)n, i);
	return (numstr);
}
