/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 11:26:42 by vicmarti          #+#    #+#             */
/*   Updated: 2021/01/29 17:07:59 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "figures.h"
#include <stdlib.h>

/*
**	To solve the intersecction of a sphere: (x-a)^2 + (y-b)^2 +(z-c)^2 = r^2
**	And a vector (x,y,z) = O + k*V
**	I've done substitution to simplify it to a quadratic ecuation whose solution
**	is k, the distance to the collision.
**	Only positive values count as solution. TODO: VERIFY!!
**	Returns NAN if no collision happens.
*/

long double	sphere_collision(void *sphere, t_vector v)
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
	if (!isnan(sol1))
		sol1 = sol1 <= 0 ? NAN : sol1;
	if (!isnan(sol2))
		sol2 = sol2 <= 0 ? NAN : sol2;
	if (isnan(sol1) && isnan(sol2))
		return (NAN);
	else if (!isnan(sol1) && isnan(sol2))
		return (sol1);
	else //TODO: Give ouput only when positive distance.
		return (sol1 <= sol2 ? sol1 : sol2);
}

void		push_sphere(t_figure **ppfig)
{
	t_figure	*aux;

	aux = malloc(sizeof(t_sphere)); //TODO: Tmp Shite.
	aux->next = *ppfig;
	aux->collision = sphere_collision;
	*ppfig = aux;
}
