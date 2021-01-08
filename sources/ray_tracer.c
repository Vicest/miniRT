/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:38:44 by vicmarti          #+#    #+#             */
/*   Updated: 2021/01/08 14:39:38 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include "math_utils.h"
#include "debug.h"

t_vector	trace_ray(t_camera c, t_resolution r, int x, int y)
{
	t_vector	ray;

	ray = c.vect;
	//TODO: Handle even/odd resolutions.
	ray.dir = vector_dir(c.vp_dist, (r[0] * 0.5L) - x, (r[1] * 0.5L) - y);
	
	if (x == 0 && y == 0)
		print_vector(ray);
	else if (x == (int)r[0] - 1 && y == 0)
		print_vector(ray);
	else if (x == 0 && y == (int)r[1] - 1)
		print_vector(ray);
	else if (x == (int)r[0] - 1 && y == (int)r[1] - 1)
		print_vector(ray);
	ray = pitch(yaw(ray , c.rota.azimuth), c.rota.latitude);
	if (x == 0 && y == 0)
		print_vector(ray);
	else if (x == (int)r[0] - 1 && y == 0)
		print_vector(ray);
	else if (x == 0 && y == (int)r[1] - 1)
		print_vector(ray);
	else if (x == (int)r[0] - 1 && y == (int)r[1] - 1)
		print_vector(ray);

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
		if(!isnan(obj_dist))
			printf("|C%.2Lf|", obj_dist);
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
