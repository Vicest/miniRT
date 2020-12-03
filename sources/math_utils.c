/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:56:04 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/03 13:28:33 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

int		is_normal(t_vector v)
{
	return (1 == sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2)));
}

//TODO: NOT HERE
int		verify_double(char *str)
{
	if (*str == '-')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
		str++;
	return (*str == '\0' ? 1 : 0);
}
