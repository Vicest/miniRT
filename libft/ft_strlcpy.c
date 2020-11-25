/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 04:31:42 by vicmarti          #+#    #+#             */
/*   Updated: 2020/01/24 16:40:27 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;

	if (!dst || !src)
		return (0);
	i = -1;
	while (src[++i] && (i + 1) < dstsize)
		dst[i] = src[i];
	if (dstsize)
		dst[i] = 0;
	while (src[i])
		i++;
	return (i);
}
