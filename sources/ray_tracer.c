/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:38:44 by vicmarti          #+#    #+#             */
/*   Updated: 2021/01/22 16:54:24 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include "math_utils.h"
#include "debug.h"
//TODO: Very tmp plz
#include "../minilibx/mlx.h"

static t_vector	gen_pray(t_camera c, t_resolution r, int x[2])
{
	t_vector	ray;

	ray = c.vect;
	//TODO: Handle even/odd resolutions better.
	ray.dir = vector_dir(c.vp_dist, (x[0] - r[0] * 0.5L), (x[1]) - r[1] * 0.5L);
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
		if (!isnan(obj_dist) && obj_dist < 9.5L)
			obj_dist = NAN;
		min_dist = fminl(min_dist, obj_dist);
		if (!isnan(min_dist) && min_dist == obj_dist)
			*nearest = geo;
		geo = geo->next;
	}
	return (min_dist);
}

//TODO: somewhere else.
//TODO: (Veeery pliz do)Perhaps code macros to separate RGB.
static t_colour	mix_colour(t_colour c1, t_colour c2)
{
	t_colour	final;

	final = 0;
	final += ft_max(c1 & 0x000000FF, c2 & 0x000000FF);
	final += ft_max(c1 & 0x0000FF00, c2 & 0x0000FF00);
	final += ft_max(c1 & 0x00FF0000, c2 & 0x00FF0000);
	return (final);
}

static t_colour	illuminate(t_scene scn, t_vector ray, long double d)
{
	t_light		*curr_lgt;
	t_colour	lgt_col;
	t_vector	lgt_ray;
	t_figure	*fig_in_path;
	int			i;

	//TODO: Illuminate computes the point to illuminate??? Nonsense!?
	//TODO: Don't I have a function for this(?) Probably should, right?
	i = -1;
	while (++i < 3)
		lgt_ray.orig.x[i] = fmal(ray.dir.x[i], d, ray.orig.x[i]);
	curr_lgt = scn.lgt;
	lgt_col = 0;
	while(curr_lgt)
	{
		//TODO: Don't I have a function for this(?) Probably should, right?
		i = -1;
		while (++i < 3)
			lgt_ray.dir.x[i] = curr_lgt->pos.x[i] - lgt_ray.orig.x[i];
		normalize(&lgt_ray);
		//TODO MINOR: Just... that's dirty and disgusting. (EEEEWW)
		d = nearest_at(scn.geo, &fig_in_path, lgt_ray); //TODO AYAYA
		if (fig_in_path == NULL)
			lgt_col = mix_colour(lgt_col, curr_lgt->col);
		curr_lgt = curr_lgt->next;
	}
	return (lgt_col);
}

//TODO: The args could be simplified (???)
void			fill_viewport(t_view view, t_scene scn, t_camera *pcam)
{
	long double	d;
	t_vector	ray;
	t_figure	*render_fig;
	t_colour	lgt_col;
	int			x[2];

	//TODO: This should be initilized somewhere else.
	pcam->img.pimg = mlx_new_image(view.mlx_ptr, scn.res[0], scn.res[1]);
	pcam->img.addr = mlx_get_data_addr(pcam->img.pimg, &pcam->img.bpp,
				&pcam->img.line_len, &pcam->img.endian);
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
			/*
				*(unsigned *)(pcam->img.addr + x[0] * (pcam->img.bpp / 8) +
					x[1] * pcam->img.line_len) = render_fig->col;
			*/
				lgt_col = illuminate(scn, ray, d);//TODO Give illuminate the coords.
				if (lgt_col == 0) //No illumination
					lgt_col = scn.amb.col;
				*(unsigned *)(pcam->img.addr + x[0] * (pcam->img.bpp / 8) +
					x[1] * pcam->img.line_len) = render_fig->col;// & lgt_col;
			}
		}
	}
}
