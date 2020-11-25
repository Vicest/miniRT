/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 22:43:03 by vicmarti          #+#    #+#             */
/*   Updated: 2020/11/03 10:17:54 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** Reverse the order of a number's digits.
*/

unsigned long	ft_revnum(unsigned long i)
{
	unsigned	long rev;

	rev = 0;
	while (i)
	{
		rev = 10 * rev + i % 10;
		i /= 10;
	}
	return (rev);
}
