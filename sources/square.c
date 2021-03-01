/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:24:22 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/01 13:10:42 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include <stdlib.h>

long double	square_collision(void *square, t_vector v)
{
	t_square	s;
	t_coord		p;
	long double	dist;

	s = *(t_square *)square;
	plane_dist(&dist, v, s.ind_term, s.normal.dir);
	p = point_at_dist(v, dist);
	if (!inside_check(p, s.normal.dir, s.vertix, 4))
		return (NAN);
	return (dist);
}

t_vector	square_normal(void *square, t_coord at, t_coord facing)
{
	t_vector	normal;

	normal.orig = at;
	normal.dir = ((t_square *)square)->normal.dir;
	vect_sub(&facing, facing, at);
	if (dot_prod(normal.dir, facing) < 0)
		scalar_prod(&normal.dir, -1.0L, normal.dir);
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
