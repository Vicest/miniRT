/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:12:10 by vicmarti          #+#    #+#             */
/*   Updated: 2020/11/30 11:30:14 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	int			sign;
	long int	nbr;

	sign = 1;
	nbr = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		sign = ',' - *str++;
	while ('0' <= *str && *str <= '9')
	{
		if ((nbr * 10 + nbr % 10) < nbr)
			return (sign == 1 ? INT_MAX : INT_MIN);
		nbr = (nbr * 10) + (*str++ - '0');
	}
	return ((int)sign * nbr);
}
