/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:38:44 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/07 19:37:00 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include "math_utils.h"
#include "colours.h"

static t_ray		gen_pray(t_camera c, int r[2], int x[2])
{
	t_ray	ray;

	//TODO: Handle even/odd resolutions better.
	ray.dir = vector_dir(c.vp_dist, (x[0] - r[0] * 0.5L), (r[1] * 0.5L - x[1]));
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

static void			set_rray(t_ray *rray, t_coord inc_dir, t_coord normal)
{
	t_coord aux;

	scalar_prod(&aux, 2 * dot_prod(normal, inc_dir), normal);
	vect_sub(&rray->dir, inc_dir, aux);
}

static void			illum(t_colour acc_col, t_scene scn, t_ray hit,
		t_figure *pfig)
{
	t_light		*curr_lgt;
	t_figure	*in_path;
	t_coord		normal;
	t_colour	shadow_col;
	long double	ld;

	curr_lgt = scn.lgt;
	normal = pfig->normal_at(pfig, hit.orig, scn.at_cam->orig);
	hit.orig = move_p(hit.orig, normal, SHADOW_B);
	ft_bzero(acc_col, sizeof(t_colour));
	while (curr_lgt)
	{
		vect_sub(&(hit.dir), curr_lgt->pos, hit.orig);
		ld = norm(hit.dir);
		scalar_prod(&(hit.dir), 1 / ld, hit.dir);
		if (ld < nearest(scn.geo, &in_path, hit) || in_path == NULL)
		{
			ft_memcpy(shadow_col, curr_lgt->col, sizeof(t_colour));
			intensity(shadow_col, fmaxl(0, dot_prod(hit.dir, normal)));
			reflect_colour(shadow_col, pfig->col, shadow_col);
			mix_colour(acc_col, shadow_col);
		}
		curr_lgt = curr_lgt->next;
	}
	mix_colour(acc_col, scn.amb);
}

/*
static void		reflect(t_scene scn, t_vector ray)
{
	t_figure	*render_fig;
	//TODO: Move collision check here.
	gen_rray();
	illum();
}*/

void				fill_viewport(t_scene scn, t_camera *pcam)
{
	t_ray		ray;
	t_coord		normal;
	t_figure	*draw;
	t_colour	lgt_col;
	int			x[2];

	x[1] = -1;
	while (++x[1] < (int)(scn.res[1]))
	{
		x[0] = -1;
		while (++x[0] < (int)(scn.res[0]))
		{
			ray = gen_pray(*pcam, scn.res, x);
			ray.orig = move_p(ray.orig, ray.dir, nearest(scn.geo, &draw, ray));
			ft_bzero(lgt_col, sizeof(t_colour));
			if (draw != NULL)
			{
				normal = draw->normal_at(draw, ray.orig, scn.at_cam->orig);
				set_rray(&ray, ray.dir, normal);
				illum(lgt_col, scn, ray, draw);
			}
			*(unsigned *)(pcam->img.addr + x[0] * (pcam->img.bpp / 8) +
				x[1] * pcam->img.line_len) = col2uint(lgt_col);
		}
	}
}
