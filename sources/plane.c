/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:54:06 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/22 12:07:15 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "figures.h"
#include <stdlib.h>
#include <stdio.h>

void		plane_dist(long double *d, t_vector v, long double iterm, t_coord n)
{
	*d = iterm - dot_prod(v.orig, n);
	*d /= dot_prod(v.dir, n);
	if (isnan(*d) || signbit(*d) == 1 || equals_zero(*d))
		*d = NAN;
}

long double	plane_collision(void *plane, t_vector v)
{
	long double	dist;
	t_plane		p;

	p = *(t_plane *)plane;
	plane_dist(&dist, v, p.ind_term, p.normal.dir);
	return (dist);
}

t_vector	plane_normal(void *plane, t_coord at, t_coord facing)
{
	t_vector	normal;

	normal.orig = at;
	normal.dir = ((t_plane*)plane)->normal.dir;
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
