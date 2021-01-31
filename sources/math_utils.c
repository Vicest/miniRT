/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:56:04 by vicmarti          #+#    #+#             */
/*   Updated: 2021/01/31 15:38:41 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include <stdlib.h>
#include <stdio.h>

int			equals_zero(long double l)
{
	return (fabsl(l) < EPSILON);
}

t_rota		inv_spherical(t_coord v)
{
	t_rota		out;
	long double	xy_len;

	xy_len = hypotl(v.x[0], v.x[1]);
	if (xy_len != 0.0L)
		out.latitude = atanl(v.x[2] / xy_len);
	else
		out.latitude = copysignl(M_PI_2, v.x[2]);
	out.azimuth = copysignl(M_PI_2, v.x[1]);
	if (v.x[0] == 0.0L && v.x[1] == 0.0L)
		out.azimuth = 0.0L;
	if (v.x[0] != 0.0L)
	{
		out.azimuth = atanl(v.x[1] / v.x[0]);
		if (v.x[0] < 0)
			out.azimuth += copysignl(M_PI, v.x[1]);
	}
	return (out);
}

t_coord		point_at_dist(t_vector ray, long double dist)
{
	t_coord		point;
	int			i;

	i = -1;
	while (++i)
		point.x[i] = fmal(dist, ray.dir.x[i], ray.orig.x[i]);
	return (point);
}

long double	norm(t_vector v)
{
	return (sqrt(pow(v.dir.x[0], 2) + pow(v.dir.x[1], 2) + pow(v.dir.x[2], 2)));
}

long double	dot_prod(t_coord v1, t_coord v2)
{
	return (v1.x[0] * v2.x[0] + v1.x[1] * v2.x[1] + v1.x[2] * v2.x[2]);
}
/*
**	https://github.com/brazzy/floating-point-gui.define
**	geeksforgeeks.com/(something something about corrctly compare floats
*/
int			is_normalized(t_vector v)
{
	return (equals_zero(fabsl(1 - norm(v))));
}

void		normalize(t_vector *v)
{
	long double	inv_norm;

	inv_norm =  1.0L / norm(*v);
	v->dir.x[0] *= inv_norm;
	v->dir.x[1] *= inv_norm;
	v->dir.x[2] *= inv_norm;
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

void		linear_solver(long double a, long double b, long double *sol)
{
	if (equals_zero(a))
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

void		quadratic_solver(long double abc[3], long double *sol1, long double *sol2)
{
	int		discriminant;

	*sol1 = NAN;
	*sol2 = NAN;
	if (equals_zero(abc[0]))
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
	else if (equals_zero(discriminant))
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
