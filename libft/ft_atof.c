/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 13:01:44 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/07 20:35:48 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

/*
**	A very basic atof.
*/

double	ft_atof(const char *a)
{
	double	f;
	int		i;
	int		decimals;
	double	sign;

	sign = a[0] == '-' ? -1 : 1;
	if (sign == -1)
		a++;
	i = 0;
	f = 0.0;
	while (ft_isdigit(a[i]))
	{
		if (f * 10 < f)
			return (INFINITY);
		f = 10 * f + (a[i++] - '0');
	}
	if (a[i++] != '.')
		return (sign * f);
	decimals = 1;
	while (ft_isdigit(a[i]))
		f += (a[i++] - '0') / pow(10, decimals++);
	return (sign * f);
}
