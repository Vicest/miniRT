/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 11:26:42 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/11 13:26:17 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "figures.h"
#include <stdlib.h>

/*
**	To solve the intersecction of a sphere: (x-a)^2 + (y-b)^2 +(z-c)^2 = r^2
**	And a vector (x,y,z) = O + k*V
**	I've done substitution to simplify it to a quadratic ecuation whose solution
**	is k, the distance to the collision.
**	Only positive values count as solution.
**	Returns NAN if no solution is found.
*/

long double	sphere_collision(void *sphere, t_vector v)
{
	long double	coefficients[3];
	long double	sol1;
	long double	sol2;
	//t_coord		aux;
	t_sphere	s;

	s = *(t_sphere *)sphere;
	/*
	aux = vect_sub(
	*/
	coefficients[0] = dot_prod(v.dir, v.dir);
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

t_vector	sphere_normal(void *s, t_coord at, t_coord facing)
{
	t_vector	normal;

	normal.orig = at;
	vect_sub(&facing, facing, at);
	normal.dir.x[0] = (at.x[0] - ((t_sphere*)s)->pos.x[0]) / ((t_sphere*)s)->r;
	normal.dir.x[1] = (at.x[1] - ((t_sphere*)s)->pos.x[1]) / ((t_sphere*)s)->r;
	normal.dir.x[2] = (at.x[2] - ((t_sphere*)s)->pos.x[2]) / ((t_sphere*)s)->r;
	if(dot_prod(normal.dir, facing) < 0)
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
