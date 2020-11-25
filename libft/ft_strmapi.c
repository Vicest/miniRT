/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 22:37:05 by vicmarti          #+#    #+#             */
/*   Updated: 2020/01/21 22:45:23 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mapped;
	size_t	i;

	if (!s || !f | !(mapped = malloc(ft_strlen(s) + 1)))
		return (NULL);
	i = -1;
	while (s[++i])
		mapped[i] = f(i, s[i]);
	mapped[i] = 0;
	return (mapped);
}
