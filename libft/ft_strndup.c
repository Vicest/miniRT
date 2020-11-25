/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 11:17:45 by vicmarti          #+#    #+#             */
/*   Updated: 2020/01/21 22:25:27 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** unit test no traga malloc
*/

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*out;

	i = 0;
	while (s1[i] && n > i)
		i++;
	if (!(out = ft_calloc(i + 1, 1)))
		return (NULL);
	out[i] = 0;
	while (i-- > 0)
		out[i] = s1[i];
	return (out);
}
