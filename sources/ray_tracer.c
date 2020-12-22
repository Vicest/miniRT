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
	/*
	printf("%Lf\n", (-(r[0] / 2.0L) + x));
	printf("%Lf\n", distance);
	printf("%Lf\n", ((r[1] / 2.0L) - y));
	*/
	ray = vector(-(r[0] / 2.0L) + x, distance, (r[1] / 2.0L) - y);
	//print_vector(ray);
	//printf("Norm:%f\n", NORM(ray));
	normalize(&ray);
	//print_vector(ray);
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
	long double	min_dist;
	long double	obj_dist;
	t_figure	*curr_fig;

	//TODO Does not use brightness ratio, maybe somewhere else makes sense
	//TODO curr_fig is just temporal
	curr_fig = scn.geo;
	min_dist = NAN;
	out = scn.amb.col;
	while (curr_fig)
	{
		obj_dist = curr_fig->collision(curr_fig, ray, scn.cam->pos);
		if (!isnan(obj_dist))
		{
			if(isnan(min_dist) ||  min_dist > obj_dist)
			{
				min_dist = obj_dist;
				out = curr_fig->col;
			}
		}
		curr_fig = curr_fig->next;
	}
	//TODO: Prolly useless
	if (isnan(min_dist))
		out = scn.amb.col;
	return (out);
}
