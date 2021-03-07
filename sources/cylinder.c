/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:04:04 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/07 19:36:35 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include <stdlib.h>

static int	in_bonds(long double d, t_cylinder c, t_coord r_orig, t_coord r_dir)
{
	t_coord		cyl_to_point;
	long double	collision_height;

	vect_sub(&cyl_to_point, move_p(r_orig, r_dir, d), c.orig);
	collision_height = dot_prod(c.dir, cyl_to_point);
	if (0 > collision_height || collision_height > c.h)
		return (0);
	return (1);
}

long double	cylinder_collision(void *cylinder, t_coord orig, t_coord dir)
{
	t_cylinder	c;
	t_coord		term[2];
	t_coord		delta_cyl;
	long double	coefficients[3];
	long double	sol[2];

	c = *(t_cylinder*)cylinder;
	scalar_prod(&term[0], dot_prod(dir, c.dir), c.dir);
	vect_sub(&term[0], dir, term[0]);
	vect_sub(&delta_cyl, orig, c.orig);
	scalar_prod(&term[1], dot_prod(delta_cyl, c.dir), c.dir);
	vect_sub(&term[1], delta_cyl, term[1]);
	coefficients[0] = dot_prod(term[0], term[0]);
	coefficients[1] = 2 * dot_prod(term[0], term[1]);
	coefficients[2] = dot_prod(term[1], term[1]) - c.r * c.r;
	quad_solve(coefficients, &sol[0], &sol[1]);
	if (!isnan(sol[0]) && (sol[0] < 0.0L || equals_zero(sol[0]) ||
				!in_bonds(sol[0], c, orig, dir)))
		sol[0] = NAN;
	if (!isnan(sol[1]) && (sol[1] < 0.0L || equals_zero(sol[1]) ||
				!in_bonds(sol[1], c, orig, dir)))
		sol[1] = NAN;
	return (fminl(sol[0], sol[1]));
}

t_coord		cylinder_normal(void *cylinder, t_coord at, t_coord facing)
{
	t_coord		normal;
	t_coord		aux;
	t_cylinder	c;

	c = *(t_cylinder*)cylinder;
	vect_sub(&aux, at, c.orig);
	scalar_prod(&aux, dot_prod(c.dir, aux), c.dir);
	vect_sum(&aux, aux, c.orig);
	vect_sub(&normal, at, aux);
	normalize(&(normal));
	vect_sub(&facing, facing, at);
	if (dot_prod(normal, facing) < 0)
		scalar_prod(&normal, -1.0L, normal);
	return (normal);
}

void		push_cylinder(t_figure **ppfig)
{
	t_figure	*aux;

	if (!(aux = malloc(sizeof(t_triangle))))
		config_err("Could not allocate mem.\n");
	aux->next = *ppfig;
	aux->collision = cylinder_collision;
	aux->normal_at = cylinder_normal;
	*ppfig = aux;
}
