/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:56:04 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/21 12:25:03 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include <stdlib.h>
#include <stdio.h>

long double	norm(t_vector v)
{
	return (sqrt(pow(v.dir.x[0], 2) + pow(v.dir.x[1], 2) + pow(v.dir.x[2], 2)));
}

/*
**	https://github.com/brazzy/floating-point-gui.define
**	geeksforgeeks.com/(something something about corrctly compare floats
*/
int			is_normalized(t_vector v, long double error)
{
	return (fabsl(1 - norm(v)) < error ? 1 : 0);
}

void		normalize(t_vector v)
{
	long double	inv_norm;

	inv_norm =  1.0L / norm(v);
	v.dir.x[0] *= inv_norm;
	v.dir.x[1] *= inv_norm;
	v.dir.x[2] *= inv_norm;
}

t_coord	vector_dir(long double x, long double y, long double z)
{
	t_coord dir;

	dir.x[0] = x;
	dir.x[1] = y;
	dir.x[2] = z;
	
	return (dir);
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
	int			i;
	int			j;

	sol.orig = v.orig;
	i = -1;
	while (++i < 3)
	{
		sol.dir.x[i] = 0;
		j = -1;
		while (++j < 3)
			sol.dir.x[i] += m.m[i][j] * v.dir.x[j];
	}
	return (sol);
}
