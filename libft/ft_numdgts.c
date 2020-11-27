/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numdgts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 01:36:59 by vicmarti          #+#    #+#             */
/*   Updated: 2020/11/03 10:20:44 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Number of digits in an integer, base 10.
*/

size_t	ft_numdgts(long long n)
{
	size_t				i;
	unsigned long long	un;

	if (n == 0)
		return (1);
	i = 1;
	un = n;
	if (n < 0)
		un = -1 * (n - 1) + 1;
	while ((un /= 10) != 0)
		i++;
	return (i);
}
