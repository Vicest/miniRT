/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:24:22 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/03 15:51:11 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include <stdlib.h>

long double	square_collision(void *square, t_coord ray_o, t_coord ray_d)
{
	t_square	s;
	t_coord		p;
	long double	dist;

	s = *(t_square *)square;
	dist = plane_dist(ray_o, ray_d, s.ind_term, s.normal);
	p = point_at_dist(ray_o, ray_d, dist);
	if (!inside_check(p, s.normal, s.vertix, 4))
		return (NAN);
	return (dist);
}

t_coord		square_normal(void *square, t_coord at, t_coord facing)
{
	t_coord		normal;

	normal = ((t_square *)square)->normal;
	vect_sub(&facing, facing, at);
	if (dot_prod(normal, facing) < 0)
		scalar_prod(&normal, -1.0L, normal);
	return (normal);
}

void		push_square(t_figure **ppfig)
{
	t_figure	*aux;

	if (!(aux = malloc(sizeof(t_square))))
		config_err("Could not allocate mem.\n");
	aux->next = *ppfig;
	aux->collision = square_collision;
	aux->normal_at = square_normal;
	*ppfig = aux;
}
