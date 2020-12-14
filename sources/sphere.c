/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 11:26:42 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/13 13:57:26 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "figures.h"
#include <stdlib.h>

/*
**	To solve the intersecction of a sphere: (x-a)^2 + (y-b)^2 +(z-c)^2 = r^2
**	And a vector (x,y,z) = O + k*V
**	I've done substitution to simplify it to a quadratic ecuation whose solution
**	is k, the distance to the collision.
**	Returns NAN if no collision happens.
*/

double	sphere_collision(t_sphere s, t_vector v, t_coord c)
{
	double	coefficients[3];
	double	sol1;
	double	sol2;

	coefficients[0] = pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2);
	coefficients[1] = 2 * v[0] * (c[0] - s.pos[0]) +
					2 * v[1] * (c[1] - s.pos[1]) +
					2 * v[2] * (c[2] - s.pos[2]);
	coefficients[2] = pow(c[0] - s.pos[0],2) + pow(c[1] - s.pos[1],2) +
					pow(c[2] - s.pos[2],2) - pow(s.r, 2);
	sol1 = NAN;
	sol2 = NAN;
	quadratic_solver(coefficients, &sol1, &sol2);
	if (isnan(sol1) && isnan(sol2))
		return (NAN);
	else if (!isnan(sol1) && isnan(sol2))
		return (sol1);
	else
		return (fabs(sol1) <= fabs(sol2) ? sol1 : sol2);
}
