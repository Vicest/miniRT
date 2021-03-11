/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:48:28 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/11 14:31:22 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include <stdlib.h>
#include <stdio.h>

static void	print_triang(t_triangle t)
{
	printf("Triangle.\n");
	printf("Vertix1: %Lf:%Lf:%Lf\n", t.vertix[0].x[0], t.vertix[0].x[1], t.vertix[0].x[2]);
	printf("Vertix2: %Lf:%Lf:%Lf\n", t.vertix[1].x[0], t.vertix[1].x[1], t.vertix[1].x[2]);
	printf("Vertix3: %Lf:%Lf:%Lf\n", t.vertix[2].x[0], t.vertix[2].x[1], t.vertix[2].x[2]);
	printf("Normal:  %Lf:%Lf:%Lf\n", t.normal.x[0], t.normal.x[1], t.normal.x[2]);
}

long double	triangle_collision(void *triangle, t_coord orig, t_coord dir)
{
	t_triangle	t;
	t_coord		p;
	long double	dist;

	t = *(t_triangle *)triangle;
	print_triang(t);
	dist = -(dot_prod(orig, t.normal) + t.ind_term);
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
