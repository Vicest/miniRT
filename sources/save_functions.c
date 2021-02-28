/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 19:55:40 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/28 20:40:18 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "validations.h"

void	store_sphere(t_scene *pscn, char **params, int p_num)
{
	if (param_num(params) != p_num)
		config_err("Invalid parameter count for sphere.\n");
	push_sphere(&pscn->geo);
	((t_sphere*)pscn->geo)->pos = validate_coordinates(params[1]);
	((t_sphere*)pscn->geo)->r = validate_double(params[2]) * 0.5L;
	validate_colour(params[3], pscn->geo->col);
}

void	store_plane(t_scene *pscn, char **params, int p_num)
{
	if (param_num(params) != p_num)
		config_err("Invalid parameter count for plane.\n");
	push_plane(&pscn->geo);
	((t_plane*)pscn->geo)->normal.orig = validate_coordinates(params[1]);
	((t_plane*)pscn->geo)->normal.dir = validate_direction(params[2]);
	((t_plane*)pscn->geo)->ind_term = dot_prod(
		((t_plane*)pscn->geo)->normal.dir, ((t_plane*)pscn->geo)->normal.orig);
	validate_colour(params[3], pscn->geo->col);
}

void	store_square(t_scene *pscn, char **params, int p_num)
{
	if (param_num(params) != p_num)
		config_err("Invalid parameter count for square.\n");
	push_plane(&pscn->geo);
	((t_plane*)pscn->geo)->normal.orig = validate_coordinates(params[1]);
	((t_plane*)pscn->geo)->normal.dir = validate_direction(params[2]);
	((t_plane*)pscn->geo)->ind_term = dot_prod(
		((t_plane*)pscn->geo)->normal.dir, ((t_plane*)pscn->geo)->normal.orig);
	validate_colour(params[3], pscn->geo->col);
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

	if (param_num(params) != p_num)
		config_err("Invalid parameter count for cylinder.\n");
	push_cylinder(&pscn->geo);
	c = ((t_cylinder*)pscn->geo);
	c->pos.orig = validate_coordinates(params[1]);
	c->pos.dir = validate_direction(params[2]);
	validate_colour(params[3], pscn->geo->col);
	c->r = validate_double(params[4]) * 0.5L;
	c->h = validate_double(params[5]);
}
