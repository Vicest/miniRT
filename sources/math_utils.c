/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:56:04 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/04 14:51:20 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include <stdlib.h>

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

void		linear_solve(long double a, long double b, long double *sol)
{
	if (equals_zero(a))
		*sol = NAN;
	else 
		*sol = -b / a;
}
void		quad_solve(long double abc[3], long double *sol1, long double *sol2)
{
	long double	discriminant;

	*sol1 = NAN;
	*sol2 = NAN;
	if (abc[0] == 0)
	{
		*sol2 = NAN;
		linear_solve(abc[0], abc[1], sol1);
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
