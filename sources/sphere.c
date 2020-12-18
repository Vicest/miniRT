/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 11:26:42 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/18 11:09:35 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "figures.h"
#include <stdlib.h>
#include <stdio.h>

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

	coefficients[0] = pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2);
	coefficients[1] = 2 * v.x * (c.x - s.pos.x) +
					2 * v.y * (c.y - s.pos.y) +
					2 * v.z * (c.z - s.pos.z);
	coefficients[2] = pow(c.x - s.pos.x,2) + pow(c.y - s.pos.y,2) +
					pow(c.z - s.pos.z,2) - pow(s.r, 2);
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
