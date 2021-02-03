/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:38:44 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/03 14:16:35 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include "math_utils.h"
#include "debug.h"

static t_vector	gen_pray(t_camera c, t_resolution r, int x[2])
{
	t_vector	ray;

	ray = c.vect;
	//TODO: Handle even/odd resolutions better.
	ray.dir = vector_dir(c.vp_dist, (x[0] - r[0] * 0.5L), (r[1] * 0.5L - x[1]));
	ray = pitch(yaw(ray , c.rota.azimuth), c.rota.latitude);
	normalize(&ray);
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

static unsigned	col2int(t_colour c)
{
	unsigned out;

	out = c[0] << 16;
	out += c[1] << 18;
	out += c[2];
	return (out);
}

//TODO: somewhere else.
//TODO: (Veeery pliz do)Perhaps code macros to separate RGB.
//TODO: More colour math neeeded, somewhere else.
static void		reflect_colour(t_colour final, t_colour c1, t_colour c2)
{
	final[0] = ft_max(c1[0] , c2[0]);
	final[1] = ft_max(c1[1] , c2[1]);
	final[2] = ft_max(c1[2] , c2[2]);
}

static void		mix_light_colour(t_colour c1, t_colour c2)
{
	c1[0] += c2[0];
	c1[1] += c2[1];
	c1[2] += c2[2];
}

static void		illuminate(t_colour lgt_col, t_scene scn, t_coord hit, t_vector nv)
{
	t_light		*curr_lgt;
	t_vector	lgt_ray;
	t_figure	*fig_in_path;
	long double	d;
	int			i;

	curr_lgt = scn.lgt;
	lgt_ray.orig = hit;
	lgt_col[0] = 0;
	lgt_col[1] = 0;
	lgt_col[2] = 0;
	while(curr_lgt)
	{
		//TODO: Don't I have a function for this(?) Probably should, right?
		i = -1;
		while (++i < 3)
		{
		//TODO: Shadow Bias
			lgt_ray.orig.x[i] += 0.1L * nv.dir.x[i];
			lgt_ray.dir.x[i] = curr_lgt->pos.x[i] - lgt_ray.orig.x[i];
		}
		normalize(&lgt_ray);
		//TODO MINOR: Just... that's dirty and disgusting. (EEEEWW)
		d = nearest_at(scn.geo, &fig_in_path, lgt_ray); //TODO AYAYA
		if (fig_in_path == NULL || equals_zero(d))
			mix_light_colour(lgt_col, curr_lgt->col);
		curr_lgt = curr_lgt->next;
	}
}

//TODO: The args could be simplified (???)
void			fill_viewport(t_scene scn, t_camera *pcam)
{
	long double	d;
	t_vector	ray;
	t_figure	*render_fig;
	t_colour	lgt_col;
	int			x[2];

	lgt_col[0] = 0;
	lgt_col[1] = 0;
	lgt_col[2] = 0;
	x[1] = -1;
	while (++x[1] < (int)(scn.res[1]))
	{
		x[0] = -1;
		while (++x[0] < (int)(scn.res[0]))
		{
			render_fig = NULL; //Sholdn't be needed.
			ray = gen_pray(*pcam, scn.res, x);
			//TODO:If not hits. I'm certain this could be simpler, rethink it.
			d = nearest_at(scn.geo, &render_fig, ray);
			if (render_fig == NULL)
				*(unsigned *)(pcam->img.addr + x[0] * (pcam->img.bpp / 8) +
					x[1] * pcam->img.line_len) = 0;
			else
			{
				ray.orig = point_at_dist(ray, d);
				illuminate(lgt_col, scn, ray.orig, render_fig->normal_at(render_fig, ray.orig));//TODO Give illuminate the coords.
				reflect_colour(lgt_col, render_fig->col, lgt_col);
				*(unsigned *)(pcam->img.addr + x[0] * (pcam->img.bpp / 8) +
					x[1] * pcam->img.line_len) = col2int(lgt_col);
			}
		}
	}
}
