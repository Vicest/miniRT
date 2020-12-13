/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:56:04 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/13 14:05:25 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include <stdlib.h>

int		is_normal(t_vector v)
{
	return (1 == sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2)));
}

/*
**	Solve a linear equation in the form of ax + b = 0-
**	Parameter sol is where the solution is stored.
**	Sol can be redirected to NULL, just be cautious.
**	Infinite solutions are treated as no solition, given as NULL.
*/

void	linear_solver(double a, double b, double *sol)
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
**	Solutions can be redirected to NULL so caution is advised.
**	If no solution is found sol1 and sol2 point to NULL.
**	For a single solution sol2 points to NULL
*/

void	quadratic_solver(double abc[3], double *sol1, double *sol2)
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
