/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:38:44 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/21 13:55:15 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include "math_utils.h"

t_vector	trace_ray(t_camera c, t_resolution r, int x, int y)
{
	t_vector	ray;
	long double	distance;

	//TODO: Handle even/odd resolutions and FOVs of 0/180.
	distance = r[0] / (2 * tan(RADIANS(c.fov / 2.0)));
	ray = vector(-r[0] / 2.0 + x, distance, r[1] / 2.0 - y);
	normalize(&ray);
	/*
	if (r[0] % 2 == 0)
		ray = cam.dir;
	else
		ray = cam.dir;
	if (r[1] % 2 == 0)
		ray = cam.dir;
	else
		ray = cam.dir;
		*/
	return (ray);
}

t_colour	compute_colour(t_scene scn, t_vector ray)
{
	t_colour	out;
	long double	collision_dist;
	long double	aux;
	t_sphere	*curr_fig;

	//TODO Does not use brightness ratio, maybe somewhere else makes sense
	//TODO curr_fig is just temporal
	curr_fig = (t_sphere*)scn.geo;
	collision_dist = NAN;
	out = scn.amb.col;
	while (curr_fig)
	{
		aux = (curr_fig)->collision(curr_fig, ray, scn.cam->pos);
		if (!isnan(aux))
			printf("%Lf: ->", aux);
			if(isnan(collision_dist) ||  collision_dist > aux)
			{
				collision_dist = aux;
				out = curr_fig->col;
				printf("%#X\n", out);
			}
		aux = NAN;
		curr_fig = curr_fig->next;
	}
	if (isnan(collision_dist))
		out = scn.amb.col;
	return (out);
}
