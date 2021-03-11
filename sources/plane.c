/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:54:06 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/11 13:26:06 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include <stdlib.h>

long double	plane_collision(void *plane, t_coord orig, t_coord dir)
{
	long double	dist;
	t_plane		p;

	p = *(t_plane *)plane;
	dist = p.ind_term - dot_prod(orig, p.normal);
	dist /= dot_prod(dir, p.normal);
	if (isnan(dist) || isinf(dist) || dist < 1)
		dist = NAN;
	return (dist);
}

t_coord				plane_normal(void *plane, t_coord at, t_coord facing)
{
	t_coord		normal;

	normal = ((t_plane *)plane)->normal;
	vect_sub(&facing, facing, at);
	if (dot_prod(normal, facing) < 0)
		scalar_prod(&normal, -1.0L, normal);
	return (normal);
}

void				push_plane(t_figure **ppfig)
{
	t_figure	*aux;

	if (!(aux = malloc(sizeof(t_triangle))))
		config_err("Could not allocate mem.\n");
	aux->next = *ppfig;
	aux->collision = plane_collision;
	aux->normal_at = plane_normal;
	*ppfig = aux;
}
