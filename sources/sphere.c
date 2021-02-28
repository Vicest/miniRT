/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 11:26:42 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/28 20:14:58 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "figures.h"
#include <stdlib.h>

long double	sphere_collision(void *sphere, t_vector v)
{
	long double	coefficients[3];
	long double	sol1;
	long double	sol2;
	t_coord		p_m_c;
	t_sphere	s;

	s = *(t_sphere *)sphere;
	vect_sub(&p_m_c, v.orig, s.pos);
	coefficients[0] = 1;
	coefficients[1] = 2 * dot_prod(v.dir, p_m_c);
	coefficients[2] = dot_prod(p_m_c, p_m_c) - s.r * s.r;
	//sol1 = NAN;
	//sol2 = NAN;
	quadratic_solver(coefficients, &sol1, &sol2);
	if (!isnan(sol1) && (sol1 < 0.0L))// || equals_zero(sol1)))
		sol1 = NAN;
	if (!isnan(sol2) && (sol2 < 0.0L))// || equals_zero(sol2)))
		sol2 = NAN;
	return (fminl(sol1, sol2));
}

t_vector	sphere_normal(void *s, t_coord at, t_coord facing)
{
	t_vector	normal;

	normal.orig = at;
	vect_sub(&normal.dir, at, ((t_sphere*)s)->pos);
	normalize(&(normal.dir));
	vect_sub(&facing, facing, at);
	if (dot_prod(normal.dir, facing) < 0)
		scalar_prod(&normal.dir, -1.0L, normal.dir);
	return (normal);
}

void		push_sphere(t_figure **ppfig)
{
	t_figure	*aux;

	aux = malloc(sizeof(t_sphere)); //TODO: Tmp Shite.
	aux->next = *ppfig;
	aux->collision = sphere_collision;
	aux->normal_at = sphere_normal;
	*ppfig = aux;
}
