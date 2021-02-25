/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:38:44 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/25 15:38:53 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include "math_utils.h"
#include "debug.h"

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

static unsigned	col2int(t_colour c)
{
	unsigned out;

	out = c[0] << 16;
	out += c[1] << 8;
	out += c[2];
	return (out);
}

//TODO: somewhere else.
//TODO: (Veeery pliz do)Perhaps code macros to separate RGB.
//TODO: More colour math neeeded, somewhere else.
static void		reflect_colour(t_colour final, t_colour c1, t_colour c2)
{
	final[0] = ft_min((int)c1[0] , (int)c2[0]);
	final[1] = ft_min((int)c1[1] , (int)c2[1]);
	final[2] = ft_min((int)c1[2] , (int)c2[2]);
}

static void		apply_light_brightness(t_colour c, long double b)
{

	int	i;

	i = -1;
	while (++i < 3)
	{
		if ((unsigned)(c[i] * b) > 255)
			c[i] = 255;
		else
			c[i] *= b;
	}
}

static void		mix_light_colour(t_colour c1, t_colour c2)
{

	int	i;

	i = -1;
	while (++i < 3)
	{
		if ((unsigned char)(c1[i] + c2[i]) < c1[i])
			c1[i] = 255;
		else
			c1[i] += c2[i];
	}
}

static t_colour		*illuminate(t_scene scn, t_vector refl_ray, t_figure *pfig)
{
	t_light		*curr_lgt;
	t_vector	nv;
	t_figure	*fig_in_path;
	t_colour	aux;
	t_colour	acc_col;
	long double	lightd;
	long double	d;

	curr_lgt = scn.lgt;
	nv = pfig->normal_at(pfig, refl_ray.orig, scn.at_cam->vect.orig);
	refl_ray.dir = nv.dir;
	refl_ray.orig = point_at_dist(refl_ray, SHADOW_B);
	ft_memcpy(acc_col, scn.amb.col, sizeof(unsigned char) * 3);
	while(curr_lgt)
	{
		vect_sub(&(refl_ray.dir), curr_lgt->pos, refl_ray.orig);
		lightd = norm(refl_ray.dir);
		scalar_prod(&(refl_ray.dir), 1 / lightd, refl_ray.dir);
		d = nearest_at(scn.geo, &fig_in_path, refl_ray);
		if (fig_in_path == NULL || d > lightd) //equals_zero(d))
		{
			ft_memcpy(aux, curr_lgt->col, sizeof(char) * 3);
			apply_light_brightness(aux, fmaxl(0, dot_prod(refl_ray.dir, nv.dir)));
			mix_light_colour(acc_col, aux);
		}
		curr_lgt = curr_lgt->next;
	}
	return (&acc_col);
}

//TODO: The args could be simplified (???)
void			fill_viewport(t_scene scn, t_camera *pcam)
{
	long double	d;
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
			//TODO:If not hits. I'm certain this could be simpler, rethink it.
			d = nearest_at(scn.geo, &render_fig, ray);
			if (render_fig == NULL)
				*(unsigned *)(pcam->img.addr + x[0] * (pcam->img.bpp / 8) +
					x[1] * pcam->img.line_len) = 0;
			else
			{
				ray.orig = point_at_dist(ray, d);
				illuminate(lgt_col, scn, ray, render_fig);
				reflect_colour(lgt_col, render_fig->col, lgt_col);
				*(unsigned *)(pcam->img.addr + x[0] * (pcam->img.bpp / 8) +
					x[1] * pcam->img.line_len) = col2int(lgt_col);
			}
		}
	}
}
