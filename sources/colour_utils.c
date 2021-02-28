/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:20:47 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/28 20:08:57 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colours.h"

unsigned	col2uint(t_colour c)
{
	unsigned out;

	out = c[0] << 16;
	out += c[1] << 8;
	out += c[2];
	return (out);
}

void		mix_colour(t_colour c1, t_colour c2)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if ((unsigned char)(c1[i] + c2[i]) < c1[i])
			c1[i] = 255;
		else
			c1[i] += c2[i];
	}
}

void		intensity(t_colour c, long double i_factor)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if ((unsigned)(c[i] * i_factor) > 255)
			c[i] = 255;
		else
			c[i] *= i_factor;
	}
}

void		reflect_colour(t_colour final, t_colour c1, t_colour c2)
{
	final[0] = ft_min((int)c1[0], (int)c2[0]);
	final[1] = ft_min((int)c1[1], (int)c2[1]);
	final[2] = ft_min((int)c1[2], (int)c2[2]);
}
