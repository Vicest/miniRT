/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:48:56 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/13 12:48:58 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "validations.h"
#include "figures.h"

/*
**	Resolution, can only be set once, and must be exactly two values.
*/

void	store_resolution(t_scene *pscn, char **element)
{
	if (pscn->flags & FLAG_RES)
		return ;//TODO Error handling, resolution already assigned
	pscn->res[0] = validate_int(element[1], 1, MAX_XRES);
	pscn->res[1] = validate_int(element[2], 1, MAX_YRES);
	pscn->flags |= FLAG_RES;
	if (element[3] != NULL)
	{
		write(1,element[3], 2);
		printf("STRERR: %s\n", strerror(5));
		exit(-1);//TODO: Error handling, too many values for resolution.
	}
}

/*
**	Ambient, can only be set once, and must be exactly a double and a colour.
*/

void	store_ambient(t_scene *pscn, char **element)
{
	if (pscn->flags & FLAG_AMB)
		return ;//TODO Error handling, ambient light already assigned.
	pscn->amb.b_ratio = validate_double(element[1]);//, 0.0, 1.0);
	pscn->amb.col = validate_colour(element[2]);
	pscn->flags |= FLAG_AMB;
	if (element[3] != NULL)
		return ; //TODO: Error handling, too many values for resolution.
}

void	store_camera(t_scene *pscn, char **params)
{
	int i;
	i = 0;
	while (i < 4 && params[i])
		i++;
	if (i != 4 || params[i])
		exit (-1); //TODO Error handling bad param number,
	push_camera(&(pscn->cam));
	pscn->cam->pos = validate_coordinates(params[1]);
	pscn->cam->dir = validate_vector(params[2]);
	pscn->cam->fov = validate_int(params[3], 0, 180);
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
	int i;

	i = 0;
	while (i < 4 && params[i])
		i++;
	if (i != 4 || params[i])
		exit (-1); //TODO Error handling bad param number,
	pscn->sp = malloc(sizeof(t_sphere)); //TODO: Temp shite
	pscn->sp->pos = validate_coordinates(params[1]);
	pscn->sp->r = validate_double(params[2]);
	pscn->sp->col = validate_colour(params[3]);
}
