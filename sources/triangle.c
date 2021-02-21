/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:48:28 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/21 21:07:16 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include <stdlib.h>

long double	triangle_collision(void *triangle, t_vector v)
{
	(void) triangle;
	(void) v;
	return (-0.01);
}

t_vector	triangle_normal(void *t, t_coord at, t_coord facing)
{
	t_vector	normal;

	normal.orig = at;
	normal.dir = ((t_triangle*)t)->normal;
	vect_sub(&facing, facing, at);
	if(dot_prod(normal.dir, facing) < 0)
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
