/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 19:55:40 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/04 14:46:36 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "validations.h"

void	store_sphere(t_scene *pscn, char **params, int p_num)
{
	t_sphere	*s;

	if (param_num(params) != p_num)
		config_err("Invalid parameter count for sphere.\n");
	push_sphere(&pscn->geo);
	s = (t_sphere *)pscn->geo;
	s->pos = validate_coordinates(params[1]);
	s->r = validate_double(params[2]) * 0.5L;
	validate_colour(params[3], pscn->geo->col);
}

void	store_plane(t_scene *pscn, char **params, int p_num)
{
	t_plane		*p;

	if (param_num(params) != p_num)
		config_err("Invalid parameter count for plane.\n");
	push_plane(&pscn->geo);
	p = (t_plane *)pscn->geo;
	p->centre = validate_coordinates(params[1]);
	p->normal = validate_direction(params[2]);
	p->ind_term = dot_prod(p->normal, p->centre);
	validate_colour(params[3], pscn->geo->col);
}

void	store_square(t_scene *pscn, char **params, int p_num)
{
	t_square	*s;
	t_coord		aux;
	long double vert_to_centre;

	if (param_num(params) != p_num)
		config_err("Invalid parameter count for square.\n");
	push_square(&pscn->geo);
	s = (t_square *)pscn->geo;
	s->centre = validate_coordinates(params[1]);
	s->normal = validate_direction(params[2]);
	s->ind_term = dot_prod(s->normal, s->centre);
	vert_to_centre = validate_double(params[3]) * M_SQRT1_2;
	aux = vector_dir(1.0L, 0.0L, 0.0L);
	if (equals_zero(1 - fabsl(dot_prod(aux, s->normal))))
		aux = vector_dir(0.0L, 1.0L, 0.0L);
	scalar_prod(&s->vertix[0], vert_to_centre, aux);
	vect_sum(&s->vertix[0], s->vertix[0], s->centre);
	scalar_prod(&s->vertix[2], -vert_to_centre, aux);
	vect_sum(&s->vertix[2], s->vertix[2], s->centre);
	cross_prod(&aux, aux, s->normal);
	scalar_prod(&s->vertix[1], vert_to_centre, aux);
	vect_sum(&s->vertix[1], s->vertix[1], s->centre);
	scalar_prod(&s->vertix[3], -vert_to_centre, aux);
	vect_sum(&s->vertix[3], s->vertix[3], s->centre);
	validate_colour(params[4], pscn->geo->col);
}

void	store_triangle(t_scene *pscn, char **params, int p_num)
{
	t_triangle	*t;
	t_coord		sides[2];

	if (param_num(params) != p_num)
		config_err("Invalid parameter count for triangle.\n");
	push_triangle(&pscn->geo);
	t = (t_triangle*)pscn->geo;
	t->vertix[0] = validate_coordinates(params[1]);
	t->vertix[1] = validate_coordinates(params[2]);
	t->vertix[2] = validate_coordinates(params[3]);
	vect_sub(sides, t->vertix[1], t->vertix[0]);
	vect_sub(&sides[1], t->vertix[2], t->vertix[0]);
	normalize(&sides[0]);
	normalize(&sides[1]);
	cross_prod(&(t->normal), sides[0], sides[1]);
	normalize(&(t->normal));
	t->ind_term = dot_prod(t->normal, t->vertix[0]);
	validate_colour(params[4], pscn->geo->col);
}

void	store_cylinder(t_scene *pscn, char **params, int p_num)
{
	t_cylinder	*c;
	t_coord		aux;

	if (param_num(params) != p_num)
		config_err("Invalid parameter count for cylinder.\n");
	push_cylinder(&pscn->geo);
	c = ((t_cylinder*)pscn->geo);
	c->orig = validate_coordinates(params[1]);
	c->dir = validate_direction(params[2]);
	validate_colour(params[3], pscn->geo->col);
	c->r = validate_double(params[4]) * 0.5L;
	c->h = validate_double(params[5]);
	aux = point_at_dist(c->orig, c->dir,  c->h);
	ft_memcpy(&c->end, &aux, sizeof(t_coord));
}
