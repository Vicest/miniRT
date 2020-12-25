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
#include "debug.h"

t_vector	trace_ray(t_camera c, t_resolution r, int x, int y)
{
	t_vector	ray;
	long double	distance;
	long double	vert_angle;
	long double	hor_angle;

	//TODO: Handle even/odd resolutions and FOVs of 0/180.
	ray = c.vect;
	distance = r[0] / (2 * tan(RADIANS(c.fov / 2.0)));
	vert_angle = M_PI * 0.5L - acosl(ray.dir.x[2]);
	hor_angle = fabsl(sinl(vert_angle)) < 0.000000001L ?
			0 : asinl(ray.dir.x[1] / sinl(vert_angle));
	ray = vector(-(r[0] / 2.0L) + x, distance, (r[1] / 2.0L) - y);
	normalize(ray);
	//TODO: Rotates on weird angles.
	ray = pitch(yaw(ray ,hor_angle), vert_angle);
	if (x == 0 && y == 0)
	{
		printf("Rotate: V%Lf-|-H%LF\n", vert_angle, hor_angle);
		print_vector(ray);
	} else if (x == (int)r[0] - 1 && y == 0)
	{
		printf("Rotate: V%Lf-|-H%LF\n", vert_angle, hor_angle);
		print_vector(ray);
	} else if (x == 0 && y == (int)r[1] - 1)
	{
		printf("Rotate: V%Lf-|-H%LF\n", vert_angle, hor_angle);
		print_vector(ray);
	} else if (x == (int)r[0] - 1 && y == (int)r[1] - 1)
	{
		printf("Rotate: V%Lf-|-H%LF\n", vert_angle, hor_angle);
		print_vector(ray);
	}
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
		obj_dist = curr_fig->collision(curr_fig, ray);
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
