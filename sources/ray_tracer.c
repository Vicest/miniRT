/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:38:44 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/11 14:12:00 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include "math_utils.h"
#include "colours.h"

static t_ray		gen_pray(t_camera c, int r[2], int x[2])
{
	t_ray	ray;

	ray.dir = vector_dir(c.vp_dist, (x[0] - r[0] * 0.5L - r[0] % 2),
			(r[1] * 0.5L - x[1] - r[1] % 2));
	yaw(&ray.dir, ray.dir, c.rota.azimuth);
	pitch(&ray.dir, ray.dir, c.rota.latitude);
	normalize(&(ray.dir));
	ray.orig = c.orig;
	ft_bzero(&ray.col, sizeof(t_colour));
	return (ray);
}

static long double	nearest(t_figure *geo, t_figure **nearest, t_ray ray)
{
	long double	obj_dist;
	long double	min_dist;

	*nearest = NULL;
	min_dist = NAN;
	while (geo)
	{
		obj_dist = geo->collision(geo, ray.orig, ray.dir);
		min_dist = fminl(min_dist, obj_dist);
		if (!isnan(min_dist) && min_dist == obj_dist)
			*nearest = geo;
		geo = geo->next;
	}
	return (min_dist);
}

/*
static void			set_rray(t_ray *rray, t_coord inc_dir, t_coord normal)
{
	t_coord aux;

	scalar_prod(&aux, 2 * dot_prod(normal, inc_dir), normal);
	vect_sub(&rray->dir, inc_dir, aux);
}
*/

static void			illum(t_scene scn, t_ray *hit, t_figure *pfig)
{
	t_light		*curr;
	t_figure	*in_path;
	t_coord		normal;
	t_colour	shadow;
	long double	ld;

	curr = scn.lgt;
	normal = pfig->normal_at(pfig, hit->orig, scn.at_cam->orig);
	hit->orig = move_p(hit->orig, normal, SHADOW_B);
	ft_bzero(hit->col, sizeof(t_colour));
	while (curr)
	{
		vect_sub(&(hit->dir), curr->pos, hit->orig);
		ld = norm(hit->dir);
		scalar_prod(&(hit->dir), 1 / ld, hit->dir);
		if (ld < nearest(scn.geo, &in_path, *hit) || in_path == NULL)
		{
			ft_memcpy(shadow, curr->col, sizeof(t_colour));
			intensity(shadow, fmaxl(0, curr->b * dot_prod(hit->dir, normal)));
			filter_colour(shadow, pfig->col, shadow);
			mix_colour(hit->col, shadow);
		}
		curr = curr->next;
	}
	mix_colour(hit->col, scn.amb);
}

void				fill_viewport(t_scene scn, t_camera *pcam)
{
	long double	d;
	t_figure	*draw;
	t_ray		ray;
	int			x[2];

	x[1] = -1;
	while (++x[1] < (int)(scn.res[1]))
	{
		x[0] = -1;
		while (++x[0] < (int)(scn.res[0]))
		{
			ray = gen_pray(*pcam, scn.res, x);
			d = nearest(scn.geo, &draw, ray);
			ray.orig = move_p(ray.orig, ray.dir, d);
			ft_bzero(ray.col, sizeof(t_colour));
			if (draw != NULL && d > 0)
				illum(scn, &ray, draw);
			*(unsigned *)(pcam->img.addr + x[0] * (pcam->img.bpp / 8) +
				x[1] * pcam->img.line_len) = col2uint(ray.col);
		}
	}
}
