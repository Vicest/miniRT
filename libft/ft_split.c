/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 14:20:20 by vicmarti          #+#    #+#             */
/*   Updated: 2020/01/19 21:07:10 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	words(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		i++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (i);
}

static size_t	word_size(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void		*clean(char **garbage, size_t items)
{
	while (items-- > 0)
		free(garbage[items]);
	free(garbage);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		wlen;
	int		i_cpy;
	char	**out;

	if (!s || !(out = malloc(sizeof(char*) * (words(s, c) + 1))))
		return (NULL);
	while (*s && *s == c)
		s++;
	i = 0;
	while (*s)
	{
		wlen = word_size(s, c);
		if (!(out[i] = malloc(sizeof(char) * (wlen + 1))))
			return (clean(out, i));
		i_cpy = 0;
		while (i_cpy < wlen)
			out[i][i_cpy++] = *s++;
		out[i][i_cpy] = 0;
		while (*s && *s == c)
			s++;
		i++;
	}
	out[i] = NULL;
	return (out);
}
