/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 03:18:54 by vicmarti          #+#    #+#             */
/*   Updated: 2020/01/22 22:46:32 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst && dst[i])
		i++;
	j = -1;
	while (src[++j] && (j + i + 1) < dstsize)
		dst[j + i] = src[j];
	if (i < dstsize)
		dst[i + j] = 0;
	while (src[j])
		j++;
	if (dstsize < i)
		return (dstsize + j);
	return (i + j);
}
