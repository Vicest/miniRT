/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 10:57:52 by vicmarti          #+#    #+#             */
/*   Updated: 2020/01/22 14:37:02 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*cpy;

	if ((!dst && !src) || dst == src)
		return (dst);
	if (src < dst)
	{
		while (--len + 1)
			*(unsigned char*)(dst + len) = *(unsigned char*)(src + len);
	}
	else
	{
		cpy = dst;
		while (--len + 1)
			*(unsigned char*)cpy++ = *(unsigned char*)src++;
	}
	return (dst);
}
