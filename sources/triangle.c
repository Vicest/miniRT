/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:48:28 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/28 20:14:26 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include <stdlib.h>

long double	triangle_collision(void *triangle, t_vector v)
{
	t_triangle	t;
	t_coord		side[2];
	t_coord		p;
	int			sign;
	long double	dist;

	t = *(t_triangle *)triangle;
	plane_dist(&dist, v, t.ind_term, t.normal);
	p = point_at_dist(v, dist);
	vect_sub(&side[0], p, t.vertix[0]);
	vect_sub(&side[1], t.vertix[1], t.vertix[0]);
	cross_prod(&side[0], side[0], side[1]);
	sign = signbit(dot_prod(side[0], t.normal));
	vect_sub(&side[0], p, t.vertix[1]);
	vect_sub(&side[1], t.vertix[2], t.vertix[1]);
	cross_prod(&side[0], side[0], side[1]);
	if (sign != signbit(dot_prod(side[0], t.normal)))
		return (NAN);
	vect_sub(&side[0], p, t.vertix[2]);
	vect_sub(&side[1], t.vertix[0], t.vertix[2]);
	cross_prod(&side[0], side[0], side[1]);
	if (sign != signbit(dot_prod(side[0], t.normal)))
		return (NAN);
	return (dist);
}

t_vector	triangle_normal(void *t, t_coord at, t_coord facing)
{
	t_vector	normal;

	normal.orig = at;
	normal.dir = ((t_triangle*)t)->normal;
	vect_sub(&facing, facing, at);
	if (dot_prod(normal.dir, facing) < 0)
		scalar_prod(&normal.dir, -1.0L, normal.dir);
	return (normal);
}

void		push_triangle(t_figure **ppfig)
{
	t_figure *aux;

	if (!(aux = malloc(sizeof(t_triangle))))
		perror("Error\n");
	aux->next = *ppfig;
	aux->collision = triangle_collision;
	aux->normal_at = triangle_normal;
	*ppfig = aux;
}
