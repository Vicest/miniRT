/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:48:28 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/01 13:10:40 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include <stdlib.h>

int			inside_check(t_coord p, t_coord nv, t_coord *vertix, int v_num)
{
	t_coord		side;
	t_coord		v_to_p;
	int			sign_cnt;
	int			i;

	sign_cnt = 0;
	i = -1;
	while(++i < v_num)
	{
		vect_sub(&v_to_p, p, vertix[i]);
		vect_sub(&side, vertix[i], vertix[(i + 1) % v_num]);
		cross_prod(&side, side, v_to_p);
		if (signbit(dot_prod(side, nv)) == 1)
			sign_cnt++;
	}
	return (sign_cnt == 0 || sign_cnt == v_num);
}

long double	triangle_collision(void *triangle, t_vector v)
{
	t_triangle	t;
	t_coord		p;
	long double	dist;

	t = *(t_triangle *)triangle;
	plane_dist(&dist, v, t.ind_term, t.normal);
	p = point_at_dist(v, dist);
	if (!inside_check(p, t.normal, t.vertix, 3))
		return (NAN);
	return (dist);
}

t_vector	triangle_normal(void *t, t_coord at, t_coord facing)
{
	t_vector	normal;

	normal.orig = at;
	normal.dir = ((t_triangle *)t)->normal;
	vect_sub(&facing, facing, at);
	if (dot_prod(normal.dir, facing) < 0)
		scalar_prod(&normal.dir, -1.0L, normal.dir);
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
