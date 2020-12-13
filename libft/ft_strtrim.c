/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:54:40 by vicmarti          #+#    #+#             */
/*   Updated: 2020/01/14 14:58:16 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	char		*trimmed;
	size_t		trimlen;

	trimlen = 0;
	if (!s1 || !set)
		return (NULL);
	while (*s1 && NULL != ft_strchr(set, *s1))
		s1++;
	start = s1;
	while (*s1++)
		trimlen++;
	while (trimlen && NULL != ft_strchr(set, *--s1))
		trimlen--;
	if (NULL == (trimmed = malloc(trimlen + 1)))
		return (trimmed);
	ft_strlcpy(trimmed, start, trimlen + 1);
	return (trimmed);
}
