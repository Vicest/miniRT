/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:54:06 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/19 18:40:17 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "figures.h"
#include <stdlib.h>
#include <stdio.h>

long double	plane_collision(void *plane, t_vector v)
{
	long double	dist;
	t_plane		p;

	p = *(t_plane *)plane;
	dist = p.ind_term - dot_prod(v.orig, p.nvect.dir);
	dist /= dot_prod(v.dir, p.nvect.dir);
	if (isnan(dist) || signbit(dist) == 1 || equals_zero(dist))
		return (NAN);
	return (dist);
}

t_vector	plane_normal(void *plane, t_coord at, t_coord facing)
{
	t_vector	normal;

	normal.orig = at;
	normal.dir = ((t_plane*)plane)->nvect.dir;
	vect_sub(&facing, facing, at);
	if(dot_prod(normal.dir, facing) < 0)
		scalar_prod(&normal.dir, -1.0L, normal.dir);
	return (normal);
}

void		push_plane(t_figure **ppfig)
{
	t_figure	*aux;

	aux = malloc(sizeof(t_plane)); //TODO: Tmp Shite.
	aux->next = *ppfig;
	aux->collision = plane_collision;
	aux->normal_at = plane_normal;
	*ppfig = aux;
}
