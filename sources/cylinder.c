/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:04:04 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/28 20:11:19 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "figures.h"
#include <stdlib.h>

static int	in_bonds(long double d, long double h, t_vector v, t_vector c_vec)
{
	t_coord		cyl_to_point;
	long double	collision_height;

	vect_sub(&cyl_to_point, point_at_dist(v, d), c_vec.orig);
	collision_height = dot_prod(c_vec.dir, cyl_to_point);
	if (0 > collision_height || collision_height > h * h)
		return (0);
	return (1);
}

long double	cylinder_collision(void *cylinder, t_vector v)
{
	t_cylinder	c;
	t_coord		a;
	t_coord		b;
	t_coord		delta_cyl;
	//t_coord		p_m_x1;
	//t_coord		p_m_x2;

	long double	coefficients[3];
	long double	sol[2];

	c = *(t_cylinder*)cylinder;
	/*
	vect_sub(&p_m_x1, v.orig, c.pos.orig);
	vect_sub(&p_m_x2, v.orig, vect_sum(&p_m_x2, c.pos.orig, c.pos.dir));
	cross_prod(&b, p_m_x1, p_m_x2);
	vect_sum(&a, cross_prod(&a, v.dir, p_m_x2), cross_prod(&a, p_m_x1, v.dir));
	*/
	scalar_prod(&a, dot_prod(v.dir, c.pos.dir), c.pos.dir);
	vect_sub(&a, v.dir, a);
	vect_sub(&delta_cyl, v.orig, c.pos.orig);
	scalar_prod(&b, dot_prod(delta_cyl, c.pos.dir), c.pos.dir);
	vect_sub(&b, delta_cyl, b);

	coefficients[0] = dot_prod(a, a);
	coefficients[1] = 2 * dot_prod(a, b);
	coefficients[2] = dot_prod(b, b) - /*c.h * c.h **/ c.r * c.r;
	quadratic_solver(coefficients, &sol[0], &sol[1]);
	if (!isnan(sol[0]) && (sol[0] < 0.0L || equals_zero(sol[0]) ||
				!in_bonds(sol[0], c.h, v, c.pos)))
		sol[0] = NAN;
	if (!isnan(sol[1]) && (sol[1] < 0.0L || equals_zero(sol[1]) ||
				!in_bonds(sol[1], c.h, v, c.pos)))
		sol[1] = NAN;
	return (fminl(sol[0], sol[1]));
}

t_vector	cylinder_normal(void *cylinder, t_coord at, t_coord facing)
{
	t_vector	normal;
	t_vector	aux;
	t_cylinder	c;

	c = *(t_cylinder*)cylinder;
	normal.orig = at;
	vect_sub(&aux.dir, at, c.pos.orig);
	scalar_prod(&aux.dir, dot_prod(c.pos.dir, aux.dir), c.pos.dir);
	vect_sum(&aux.dir, aux.dir, c.pos.orig);
	vect_sub(&normal.dir, at, aux.dir);
	normalize(&(normal.dir));
	vect_sub(&facing, facing, at);
	if (dot_prod(normal.dir, facing) < 0)
		scalar_prod(&normal.dir, -1.0L, normal.dir);
	return (normal);
}

void		push_cylinder(t_figure **ppfig)
{
	t_figure	*aux;

	aux = malloc(sizeof(t_cylinder)); //TODO: Tmp Shite.
	aux->next = *ppfig;
	aux->collision = cylinder_collision;
	aux->normal_at = cylinder_normal;
	*ppfig = aux;
}
