/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:56:04 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/15 14:42:16 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include <stdlib.h>
#include <stdio.h>


void		set_vector(t_vector *v, double x, double y, double z)
{
	(*v).x = x;
	(*v).y = y;
	(*v).z = z;
}

int			is_normal(t_vector v)
{
	return (1 == sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

/*
**	Solve a linear equation in the form of ax + b = 0-
**	Parameter sol is where the solution is stored.
**	Sol can be redirected to NULL, just be cautious.
**	Infinite solutions are treated as no solition, given as NULL.
*/

void		linear_solver(double a, double b, double *sol)
{
	if (a == 0)
		*sol = NAN;
	else 
		*sol = -b / a;
}

/*
**	Solve a quadratic equation in the form of ax^2 + bx + c = 0.
**	Parameter abc is the array of coefficients, must be 3.
**	Parameter sol1 and sol2 are where solutions are stored.
**	Solutions can be redirected to NAN so caution is advised.
**	If no solution is found sol1 and sol2 point to NAN.
**	For a single solution sol2 points to NAN.
*/

void		quadratic_solver(double abc[3], double *sol1, double *sol2)
{
	int		discriminant;

	if (abc[0] == 0)
	{
		*sol2 = NAN;
		linear_solver(abc[0], abc[1], sol1);
		return ;
	}
	discriminant = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (discriminant > 0)
	{
		*sol1 = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
		*sol2 = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
	}
	else if (discriminant == 0)
	{
		*sol1 = -abc[1] / (2 * abc[0]);
		*sol2 = NAN;
	}
}

/*
**	Calculate a matrix to vector multiplication. Known as a transformation.
*/

t_vector		l_transform(t_matrix m, t_vector v)
{
	t_vector	sol;

	sol.x = m.x.x * v.x + m.x.y * v.y + m.x.z * v.z;
	sol.y = m.y.x * v.x + m.y.y * v.y + m.y.z * v.z;
	sol.z = m.z.x * v.x + m.z.y * v.y + m.z.z * v.z;
	return (sol);
}
