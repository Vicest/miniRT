/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:59:37 by vicmarti          #+#    #+#             */
/*   Updated: 2020/01/22 14:31:59 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if ((!dst && !src) || dst == src)
		return (dst);
	while (--n + 1)
		*(unsigned char*)(dst + n) = *(unsigned char*)(src + n);
	return (dst);
}
