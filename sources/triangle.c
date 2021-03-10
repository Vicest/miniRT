/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:48:28 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/10 15:23:34 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include <stdlib.h>

long double	triangle_collision(void *triangle, t_coord orig, t_coord dir)
{
	t_triangle	t;
	t_coord		p;
	long double	dist;

	t = *(t_triangle *)triangle;
	dist = t.ind_term - dot_prod(orig, t.normal);
	dist /= dot_prod(dir, t.normal);
	if (isnan(dist) || isinf(dist) || dist < 0)
		return (NAN);
	p = move_p(orig, dir, dist);
	if (!inside_check(p, t.normal, t.vertix, 3))
		return (NAN);
	return (dist);
}

t_coord		triangle_normal(void *t, t_coord at, t_coord facing)
{
	t_coord		normal;

	normal = ((t_triangle *)t)->normal;
	vect_sub(&facing, facing, at);
	if (dot_prod(normal, facing) < 0)
		scalar_prod(&normal, -1.0L, normal);
	return (normal);
}

void		push_triangle(t_figure **ppfig)
{
	t_figure *aux;

	if (!(aux = malloc(sizeof(t_triangle))))
		config_err("Could not allocate mem.\n");
	aux->next = *ppfig;
	aux->collision = triangle_collision;
	aux->normal_at = triangle_normal;
	*ppfig = aux;
}
