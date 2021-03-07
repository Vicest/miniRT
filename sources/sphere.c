/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 11:26:42 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/07 15:27:54 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include <stdlib.h>

long double		sphere_collision(void *sphere, t_coord orig, t_coord dir)
{
	long double	coefficients[3];
	long double	sol[2];
	t_coord		p_m_c;
	t_sphere	s;

	s = *(t_sphere *)sphere;
	vect_sub(&p_m_c, orig, s.pos);
	coefficients[0] = 1;
	coefficients[1] = 2 * dot_prod(dir, p_m_c);
	coefficients[2] = dot_prod(p_m_c, p_m_c) - s.r * s.r;
	quad_solve(coefficients, &sol[0], &sol[1]);
	if (!isnan(sol[0]) && (sol[0] < 0.0L || equals_zero(sol[0])))
		sol[0] = NAN;
	if (!isnan(sol[1]) && (sol[1] < 0.0L || equals_zero(sol[1])))
		sol[1] = NAN;
	return (fminl(sol[0], sol[1]));
}

t_coord			sphere_normal(void *s, t_coord at, t_coord facing)
{
	t_coord		normal;

	vect_sub(&normal, at, ((t_sphere*)s)->pos);
	normalize(&normal);
	vect_sub(&facing, facing, at);
	if (dot_prod(normal, facing) < 0)
		scalar_prod(&normal, -1.0L, normal);
	return (normal);
}
/*
t_colour		*colour(void *sphere, t_coord hit)
{
	t_sphere	*s;
	t_colour	*col;
	long double	d;

	d = norm(hit - reference);
	s = (t_sphere *)sphere;
	return (col);
}
*/
void			push_sphere(t_figure **ppfig)
{
	t_figure	*aux;

	if (!(aux = malloc(sizeof(t_sphere))))
		config_err("Could not allocate mem.\n");
	aux->next = *ppfig;
	aux->collision = sphere_collision;
	aux->normal_at = sphere_normal;
	*ppfig = aux;
}
