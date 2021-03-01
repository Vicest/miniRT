/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_functions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:48:56 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/01 11:34:28 by vicmarti         ###   ########.fr       */
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
	ratio = validate_double(params[1]);
	if (ratio < 0.0L || ratio > 1.0L)
		config_err("Ambient light ratio value must be in range [0.0,1.0].\n");
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
	pcam->vect.orig = validate_coordinates(params[1]);
	pcam->vect.dir = validate_direction(params[2]);
	pcam->fov = validate_int(params[3], 1, 179);
	pcam->vp_dist = pscn->res[0] * atanl(pscn->at_cam->fov * M_PI / 360);
	pcam->rota = inv_spherical(pcam->vect.dir);
	pcam->lr_dir = vector_dir(0, 1, 0);
	pcam->lr_dir = pitch(yaw(pcam->lr_dir, pcam->rota.azimuth), pcam->rota.latitude);
	pcam->ud_dir = vector_dir(0, 0, 1);
	pcam->ud_dir = pitch(yaw(pcam->ud_dir, pcam->rota.azimuth), pcam->rota.latitude);
}

void	store_light(t_scene *pscn, char **params, int p_num)
{
	if (param_num(params) != p_num)
		config_err("Invalid parameter count for light.\n");
	push_light(&(pscn->lgt));
	pscn->lgt->pos = validate_coordinates(params[1]);
	pscn->lgt->b_ratio = validate_double(params[2]); //TODO dbl max && bbl min, 0, 180);
	validate_colour(params[3], pscn->lgt->col);
}
