/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 11:26:42 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/20 14:47:54 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"

/*
**	To solve the intersecction of a sphere: (x-a)^2 + (y-b)^2 +(z-c)^2 = r^2
**	And a vector (x,y,z) = O + k*V
**	I've done substitution to simplify it to a quadratic ecuation whose solution
**	is k, the distance to the collision.
**	Returns NAN if no collision happens.
*/

long double	sphere_collision(void *sphere, t_vector v, t_coord c)
{
	double	coefficients[3];
	double		sol1;
	double		sol2;
	t_sphere	s;

	s = *(t_sphere *)sphere;
	coefficients[0] = pow(v.v[0], 2) + pow(v.v[1], 2) + pow(v.v[2], 2);
	coefficients[1] = 2 * v.v[0] * (c.v[0] - s.pos.v[0]) +
					2 * v.v[1] * (c.v[1] - s.pos.v[1]) +
					2 * v.v[2] * (c.v[2] - s.pos.v[2]);
	coefficients[2] = pow(c.v[0] - s.pos.v[0],2) + pow(c.v[1] - s.pos.v[1],2) +
					pow(c.v[2] - s.pos.v[2],2) - pow(s.r, 2);
	sol1 = NAN;
	sol2 = NAN;
	quadratic_solver(coefficients, &sol1, &sol2);
	if (isnan(sol1) && isnan(sol2))
		return (NAN);
	else if (!isnan(sol1) && isnan(sol2))
		return (sol1);
	else //TODO: Give ouput only when positive distance.
		return (fabs(sol1) <= fabs(sol2) ? sol1 : sol2);
}

void	push_sphere(t_scene *pscn)
{
	t_figure	*aux;

	printf("New sphere.\n");
	aux = malloc(sizeof(t_sphere)); //TODO: Tmp Shite.
	aux->next = pscn->geo;
	aux->collision = sphere_collision;
	pscn->geo = aux;
}
