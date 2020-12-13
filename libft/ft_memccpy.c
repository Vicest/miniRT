/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 10:25:28 by vicmarti          #+#    #+#             */
/*   Updated: 2020/01/21 21:42:09 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n-- > 0)
	{
		*(unsigned char*)dst = *(unsigned char*)src;
		if (*(unsigned char*)dst == (unsigned char)c)
			return (dst + 1);
		dst++;
		src++;
	}
	return (NULL);
}
