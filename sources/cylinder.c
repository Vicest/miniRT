/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:04:04 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/11 16:00:52 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "figures.h"
#include <stdlib.h>

long double	cylinder_collision(void *cylinder, t_vector v)
{
	t_cylinder	c;
	t_coord		a;
	t_coord		b;
	t_coord		p_m_x1;
	t_coord		p_m_x2;

	long double	coefficients[3];
	long double	sol1;
	long double	sol2;


	c = *(t_cylinder*)cylinder;
	vect_sub(&p_m_x1, v.orig, c.pos.orig);
	vect_sub(&p_m_x2, v.orig, c.pos.dir);
	cross_prod(&b, p_m_x1, p_m_x2);
	vect_sum(&a, cross_prod(&a, v.dir, p_m_x2), cross_prod(&a, p_m_x1, v.dir));
	coefficients[0] = dot_prod(a, a);
	coefficients[1] = 2 * dot_prod(a, b);
	coefficients[2] = dot_prod(b, b) - c.h * c.r;
	//sol1 = NAN;
	//sol2 = NAN;
	quadratic_solver(coefficients, &sol1, &sol2);
	if (!isnan(sol1) && (sol1 < 0.0L || equals_zero(sol1)))
		sol1 = NAN;
	if (!isnan(sol2) && (sol2 < 0.0L || equals_zero(sol2)))
		sol2 = NAN;
	return (fminl(sol1, sol2));
}

t_vector	cylinder_normal(void *cylinder, t_coord at, t_coord facing)
{
	t_vector	normal;
	t_vector	aux;
	t_cylinder	c;
	long double	d;

	(void)facing;
	c = *(t_cylinder*)cylinder;
	normal.orig = at;
	aux.dir = vect_sub(&aux.dir, at, c.pos.orig);
	d = dot_prod(c.pos.dir, aux.dir) / c.h;
	scalar_prod(&aux.dir, d, c.pos.dir);
	vect_sum(&aux.dir, aux.dir, c.pos.orig);
	vect_sub(&normal.dir, at, aux.dir);
	normalize(&normal);
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
