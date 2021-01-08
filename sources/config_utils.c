/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:48:56 by vicmarti          #+#    #+#             */
/*   Updated: 2021/01/08 13:34:57 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "validations.h"

/*
**	Resolution, can only be set once, and must be exactly two values.
*/

void	store_resolution(t_scene *pscn, char **element)
{
	if (pscn->flags & FLAG_RES)
		config_err("Resolution can only be defined once.\n");
	pscn->res[0] = validate_int(element[1], 1, MAX_XRES);
	pscn->res[1] = validate_int(element[2], 1, MAX_YRES);
	pscn->flags |= FLAG_RES;
	if (element[3] != NULL)
		config_err("Resolution takes only two values.\n");
}

/*
**	Ambient, can only be set once, and must be exactly a double and a colour.
*/

void	store_ambient(t_scene *pscn, char **element)
{
	if (pscn->flags & FLAG_AMB)
		config_err("Ambient light can only be defined once.\n");
	pscn->amb.b_ratio = validate_double(element[1]);//, 0.0, 1.0);
	pscn->amb.col = validate_colour(element[2]);
	pscn->flags |= FLAG_AMB;
	if (element[3] != NULL)
		config_err("Ambient light takes only two values.\n");
}

/*
**	Distance math is trigonometry for r[0] / d == tan(fov / 2)
*/

void	store_camera(t_scene *pscn, char **params)
{
	int			i;
	t_camera	*pcam;

	i = 0;
	while (i < 4 && params[i])
		i++;
	if (i != 4 || params[i])
		exit (-1); //TODO Error handling bad param number,
	push_camera(&(pscn->at_cam));
	pcam = pscn->at_cam;
	ft_bzero(&pcam->img, sizeof(t_img));
	pcam->vect.orig = validate_coordinates(params[1]);
	pcam->vect.dir = validate_direction(params[2]);
	pcam->fov = validate_int(params[3], 1, 179);//TODO 0 and 180 fov how?
	pcam->vp_dist = pscn->res[0] * atanl(pscn->at_cam->fov * M_PI /360);
	pcam->rota = inv_spherical(pcam->vect.dir);
}

void	store_light(t_scene *pscn, char **params)
{
	int i;

	i = 0;
	while (i < 4 && params[i])
		i++;
	if (i != 4 || params[i])
		exit (-1); //TODO Error handling bad param number,
	push_light(&(pscn->lgt));
	pscn->lgt->pos = validate_coordinates(params[1]);
	pscn->lgt->b_ratio = validate_double(params[2]); //TODO dbl max && bbl min, 0, 180);
	pscn->lgt->col = validate_colour(params[3]);
}

void	store_sphere(t_scene *pscn, char **params)
{
	int			i;

	i = 0;
	while (i < 4 && params[i])
		i++;
	if (i != 4 || params[i])
		config_err("Invalid parameter count for sphere, must be 3 exactly\n");
	push_sphere(&pscn->geo);
	((t_sphere*)pscn->geo)->pos = validate_coordinates(params[1]);
	((t_sphere*)pscn->geo)->r = validate_double(params[2]);
	pscn->geo->col = validate_colour(params[3]);
}

void	store_plane(t_scene *pscn, char **params)
{
	int			i;

	i = 0;
	while (params[i])
		i++;
	if (i != 4)
		config_err("Invalid parameter count for plane, must be 3 exactly\n");
	push_plane(&pscn->geo);
	((t_plane*)pscn->geo)->nvect.orig = validate_coordinates(params[1]);
	((t_plane*)pscn->geo)->nvect.dir = validate_direction(params[2]);
	pscn->geo->col = validate_colour(params[3]);
}
