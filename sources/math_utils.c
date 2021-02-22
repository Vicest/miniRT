/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:56:04 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/22 14:40:36 by vicmarti         ###   ########.fr       */
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

t_coord		point_at_dist(t_vector v, long double dist)
{
	t_coord		point;
	int			i;

	i = -1;
	while (++i < 3)
		point.x[i] = dist * v.dir.x[i] + v.orig.x[i];
		//point.x[i] = fmal(dist, v.dir.x[i], v.orig.x[i]);
	return (point);
}

long double	norm(t_coord v)
{
	return (sqrt(dot_prod(v,v)));
}

t_coord		vect_sum(t_coord *out, t_coord v1, t_coord v2)
{
	out->x[0] = v1.x[0] + v2.x[0];
	out->x[1] = v1.x[1] + v2.x[1];
	out->x[2] = v1.x[2] + v2.x[2];
	return (*out);
}

t_coord		vect_sub(t_coord *out, t_coord v1, t_coord v2)
{
	out->x[0] = v1.x[0] - v2.x[0];
	out->x[1] = v1.x[1] - v2.x[1];
	out->x[2] = v1.x[2] - v2.x[2];
	return (*out);
}

/*
t_coord		neg_vect(t_coord v)
{
	n.x
*/

t_coord		scalar_prod(t_coord *out, long double k, t_coord v)
{
	out->x[0] = k * v.x[0];
	out->x[1] = k * v.x[1];
	out->x[2] = k * v.x[2];
	return (*out);
}

long double	dot_prod(t_coord v1, t_coord v2)
{
	return (v1.x[0] * v2.x[0] + v1.x[1] * v2.x[1] + v1.x[2] * v2.x[2]);
}

t_coord		cross_prod(t_coord *out, t_coord v1, t_coord v2)
{
	out->x[0] = v1.x[1] * v2.x[2] - v1.x[2] * v2.x[1];
	out->x[1] = v1.x[0] * v2.x[2] - v1.x[2] * v2.x[0];
	out->x[2] = v1.x[0] * v2.x[1] - v1.x[1] * v2.x[0];
	return (*out);
}
/*
**	https://github.com/brazzy/floating-point-gui.define
**	geeksforgeeks.com/(something something about corrctly compare floats
*/
int			is_normalized(t_coord v)
{
	return (equals_zero(fabsl(1 - norm(v))));
}

void		normalize(t_coord *v)
{
	long double	inv_norm;

	inv_norm =  1.0L / norm(*v);
	v->x[0] *= inv_norm;
	v->x[1] *= inv_norm;
	v->x[2] *= inv_norm;
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

void		quadratic_solver(long double abc[3], long double *sol1, long double *sol2)
{
	long double	discriminant;

	*sol1 = NAN;
	*sol2 = NAN;
	if (abc[0] == 0)
	{
		*sol2 = NAN;
		linear_solver(abc[0], abc[1], sol1);
		return ;
	}
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant > 0)
	{
		discriminant = sqrt(discriminant);
		*sol1 = (-abc[1] + discriminant) / (2 * abc[0]);
		*sol2 = (-abc[1] - discriminant) / (2 * abc[0]);
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
t_coord		l_transform(t_matrix m, t_coord v)
{
	t_coord		sol;
	int			i;
	int			j;

	i = -1;
	while (++i < 3)
	{
		sol.x[i] = 0;
		j = -1;
		while (++j < 3)
			sol.x[i] += m.m[i][j] * v.x[j];
	}
	return (sol);
}
