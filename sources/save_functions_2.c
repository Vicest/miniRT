/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_functions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:48:56 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/07 19:13:54 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "validations.h"

/*
**	Resolution, can only be set once, and must be exactly two values.
*/

void	store_resolution(t_scene *pscn, char **params, int p_num)
{
	if (param_num(params) != p_num)
		config_err("Invalid parameter count for resolution.\n");
	if (pscn->flags & FLAG_RES)
		config_err("Resolution can only be defined once.\n");
	pscn->res[0] = validate_int(params[1], 1, MAX_XRES);
	pscn->res[1] = validate_int(params[2], 1, MAX_YRES);
	pscn->flags |= FLAG_RES;
}

/*
**	Ambient, can only be set once, and must be exactly a double and a colour.
*/

void	store_ambient(t_scene *pscn, char **params, int p_num)
{
	long double	ratio;

	if (param_num(params) != p_num)
		config_err("Invalid parameter count for ambient.\n");
	if (pscn->flags & FLAG_AMB)
		config_err("Ambient light can only be defined once.\n");
	ratio = validate_double(params[1], 0.0L, 1.0L);
	validate_colour(params[2], pscn->amb);
	pscn->amb[0] *= ratio;
	pscn->amb[1] *= ratio;
	pscn->amb[2] *= ratio;
	pscn->flags |= FLAG_AMB;
}

void	store_camera(t_scene *pscn, char **params, int p_num)
{
	t_camera	*pcam;

	if (param_num(params) != p_num)
		config_err("Invalid parameter count for camera.\n");
	push_camera(&(pscn->at_cam));
	pcam = pscn->at_cam;
	ft_bzero(&pcam->img, sizeof(t_img));
	pcam->orig = validate_coordinates(params[1]);
	pcam->dir = validate_coordinates(params[2]);
	if (!is_normalized(pcam->dir))
		config_err("Vector not normalized.");
	pcam->fov = validate_int(params[3], 1, 179);
	pcam->vp_dist = pscn->res[0] * atanl(pscn->at_cam->fov * M_PI / 360);
	pcam->rota = inv_spherical(pcam->dir);
	pcam->lr_dir = vector_dir(0, 1, 0);
	yaw(&pcam->lr_dir, pcam->lr_dir, pcam->rota.azimuth);
	pitch(&pcam->lr_dir, pcam->lr_dir, pcam->rota.latitude);
	pcam->ud_dir = vector_dir(0, 0, 1);
	yaw(&pcam->ud_dir, pcam->lr_dir, pcam->rota.azimuth);
	pitch(&pcam->ud_dir, pcam->lr_dir, pcam->rota.latitude);
}

void	store_light(t_scene *pscn, char **params, int p_num)
{
	if (param_num(params) != p_num)
		config_err("Invalid parameter count for light.\n");
	push_light(&(pscn->lgt));
	pscn->lgt->pos = validate_coordinates(params[1]);
	pscn->lgt->b_ratio = validate_double(params[2], 0.0L, 1.0L);
	validate_colour(params[3], pscn->lgt->col);
}

void	store_sphere(t_scene *pscn, char **params, int p_num)
{
	t_sphere	*s;

	if (param_num(params) != p_num)
		config_err("Invalid parameter count for sphere.\n");
	push_sphere(&pscn->geo);
	s = (t_sphere *)pscn->geo;
	s->pos = validate_coordinates(params[1]);
	s->r = validate_double(params[2], 0.0L, HUGE_VAL) * 0.5L;
	validate_colour(params[3], pscn->geo->col);
}
