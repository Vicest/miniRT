/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:04:04 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/11 13:30:44 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "figures.h"
#include <stdlib.h>

long double	cylinder_collision(void *sphere, t_vector v)
{
	long double	coefficients[3];
	long double	sol1;
	long double	sol2;
	t_sphere	s;

	s = *(t_sphere *)sphere;
	//TODO: A loop to ease readability.
	coefficients[0] = pow(v.dir.x[0], 2) +
					pow(v.dir.x[1], 2) +
					pow(v.dir.x[2], 2);
	coefficients[1] = 2 * (v.dir.x[0] * (v.orig.x[0] - s.pos.x[0]) +
					v.dir.x[1] * (v.orig.x[1] - s.pos.x[1]) +
					v.dir.x[2] * (v.orig.x[2] - s.pos.x[2]));
	coefficients[2] = pow(v.orig.x[0] - s.pos.x[0],2) +
					pow(v.orig.x[1] - s.pos.x[1],2) +
					pow(v.orig.x[2] - s.pos.x[2],2) - pow(s.r, 2);
	//sol1 = NAN;
	//sol2 = NAN;
	quadratic_solver(coefficients, &sol1, &sol2);
	if (!isnan(sol1) && (sol1 < 0.0L || equals_zero(sol1)))
		sol1 = NAN;
	if (!isnan(sol2) && (sol2 < 0.0L || equals_zero(sol2)))
		sol2 = NAN;
	return (fminl(sol1, sol2));
}

t_vector	cylinder_normal(void *sphere, t_coord at)
{
	t_vector	normal;

	normal.orig = at;
	normal.dir.x[0] = at.x[0] - ((t_sphere*)sphere)->pos.x[0];
	normal.dir.x[1] = at.x[1] - ((t_sphere*)sphere)->pos.x[1];
	normal.dir.x[2] = at.x[2] - ((t_sphere*)sphere)->pos.x[2];
	normalize(&normal);
	return (normal);
}

void		push_cylinder(t_figure **ppfig)
{
	t_figure	*aux;

	aux = malloc(sizeof(t_sphere)); //TODO: Tmp Shite.
	aux->next = *ppfig;
	aux->collision = cylinder_collision;
	aux->normal_at = cylinder_normal;
	*ppfig = aux;
}
