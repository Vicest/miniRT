/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:38:44 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/28 19:26:49 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include "math_utils.h"
#include "colours.h"

static t_vector	gen_pray(t_camera c, int r[2], int x[2])
{
	t_vector	ray;

	//TODO: Handle even/odd resolutions better.
	ray.dir = vector_dir(c.vp_dist, (x[0] - r[0] * 0.5L), (r[1] * 0.5L - x[1]));
	ray.dir = pitch(yaw(ray.dir , c.rota.azimuth), c.rota.latitude);
	normalize(&(ray.dir));
	ray.orig = c.vect.orig;
	return (ray);
}

static long double	nearest_at(t_figure *geo, t_figure **nearest, t_vector ray)
{
	long double	obj_dist;
	long double	min_dist;

	*nearest = NULL;
	min_dist = NAN;
	while (geo)
	{
		obj_dist = geo->collision(geo, ray);
		min_dist = fminl(min_dist, obj_dist);
		if (!isnan(min_dist) && min_dist == obj_dist)
			*nearest = geo;
		geo = geo->next;
	}
	return (min_dist);
}

static void		illuminate(t_colour acc_col, t_scene scn, t_vector hit, t_figure *pfig)
{
	t_light		*curr_lgt;
	t_figure	*in_path;
	t_vector	nv;
	t_colour	shadow_col;
	long double	ld;

	curr_lgt = scn.lgt;
	nv = pfig->normal_at(pfig, hit.orig, scn.at_cam->vect.orig);
	hit.dir = nv.dir;
	hit.orig = point_at_dist(hit, SHADOW_B);
	ft_bzero(acc_col, sizeof(t_colour));
	while(curr_lgt)
	{
		vect_sub(&(hit.dir), curr_lgt->pos, hit.orig);
		ld = norm(hit.dir);
		scalar_prod(&(hit.dir), 1 / ld, hit.dir);
		if (ld < nearest_at(scn.geo, &in_path, hit) || in_path == NULL)
		{
			ft_memcpy(shadow_col, curr_lgt->col, sizeof(t_colour));
			intensity(shadow_col, fmaxl(0, dot_prod(hit.dir, nv.dir)));
			mix_colour(acc_col, shadow_col);
		}
		curr_lgt = curr_lgt->next;
	}
	mix_colour(acc_col, scn.amb.col);
}

//TODO: The args could be simplified
void			fill_viewport(t_scene scn, t_camera *pcam)
{
	t_vector	ray;
	t_figure	*render_fig;
	t_colour	lgt_col;
	int			x[2];

	x[1] = -1;
	while (++x[1] < (int)(scn.res[1]))
	{
		x[0] = -1;
		while (++x[0] < (int)(scn.res[0]))
		{
			ray = gen_pray(*pcam, scn.res, x);
			ray.orig = point_at_dist(ray, nearest_at(scn.geo, &render_fig, ray));
			ft_bzero(lgt_col, sizeof(t_colour));
			if (render_fig != NULL)
			{
				illuminate(lgt_col, scn, ray, render_fig);
				reflect_colour(lgt_col, render_fig->col, lgt_col);
			}
			*(unsigned *)(pcam->img.addr + x[0] * (pcam->img.bpp / 8) +
				x[1] * pcam->img.line_len) = col2uint(lgt_col);
		}
	}
}
