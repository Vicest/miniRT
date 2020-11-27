/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 01:31:22 by vicmarti          #+#    #+#             */
/*   Updated: 2020/01/21 22:06:00 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	dstsize;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	dstsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(dst = malloc(dstsize)))
		return (dst);
	while (*s1)
		dst[i++] = *s1++;
	while (*s2)
		dst[i++] = *s2++;
	dst[i] = 0;
	return (dst);
}
