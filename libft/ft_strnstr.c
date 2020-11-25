/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 10:59:13 by vicmarti          #+#    #+#             */
/*   Updated: 2020/01/24 16:29:33 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t needle_len;

	if (!*needle)
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	if (!len || !*haystack)
		return (NULL);
	while (*haystack && len >= needle_len)
	{
		if (*haystack == *needle && !(ft_memcmp(haystack, needle, needle_len)))
			return ((char *)haystack);
		haystack++ && len--;
	}
	return (NULL);
}
