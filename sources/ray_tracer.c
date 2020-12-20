/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:38:44 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/20 14:57:37 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include "math_utils.h"

t_vector	trace_ray(long double angle, t_vector ref, t_coord center)
{
	t_vector	ray;

	ray = yaw(pitch(ref, angle), angle);

	return (ray);
}

t_vector	rot_vect

t_colour	compute_colour(t_scene scn, t_vector ray, t_coord c)
{
	t_colour out;

	c = scn.amb.col;//TODO Does not use brightness ratio, maybe somewhere else makes sense
	while (geo)
	return (c);
}
