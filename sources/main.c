/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:00:09 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/21 13:53:31 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../minilibx/mlx.h"
#include <stdlib.h>

#define X_CLOSE_BUTTON 17


static int	win_close(int keycode)
{
	if (keycode == KEY_ESC)
	{
		//system("leaks -quiet miniRT");
		exit(-1);
	}
	else
		printf("You pressed: %#x\n", keycode);
	return (-1);
	//mlx_destroy_window(mlx_ptr, win_ptr);
}

static int quit(void *params)
{
	(void)params;
	//system("leaks -quiet miniRT");
	printf("Lolailo\n");
	exit(-1);
	return (1);
}

static t_scene	scn_init()
{
	t_scene scn;

	scn.flags = 0;
	scn.res[0] = 0;
	scn.res[1] = 0;
	scn.amb.b_ratio = 0;
	scn.amb.col = 0;
	scn.cam = NULL;
	scn.lgt = NULL;
	scn.geo = NULL;

	return (scn);
}

static t_img	img_init()
{
	t_img out;

	out.canv = NULL;
	out.addr = NULL;
	out.bpp = 0;
	out.line_len = 0;
	out.endian = 0;
	return (out);
}

void		fill_viewport(t_scene scn, t_view view)
{
	int			x;
	int			y;
	t_vector	ray;
	t_colour	col;
	void		*img_ptr;
	t_img		img;
	//long double	c;

	img = img_init();
	img_ptr = mlx_new_image(view.mlx_ptr, scn.res[0], scn.res[1]);
	img.addr = mlx_get_data_addr(img_ptr, &img.bpp, &img.line_len, &img.endian);
	y = 0;
	while (y < (int)(scn.res[1]))
	{
		x = 0;
		while (x < (int)(scn.res[0]))
		{
			//TODO: Gotta handle cam changing.
			ray = trace_ray(*(scn.cam), scn.res,x , y);
			col = compute_colour(scn, ray);
			*(unsigned *)(img.addr + x * (img.bpp / 8) + y * img.line_len) = col;
			/*
			while (scn.geo)
			{
				c =
			col = sphere_collision(*(scn.geo), ray, scn.cam->pos);
			if (!isnan(col) && col >= 0)
			{
			*(unsigned *)(img.addr + x * img.bpp / 8 + y * img.line_len) = col;
			}
			else
				mlx_pixel_put(mlx_ptr, view.win_ptr, x, y, scn.amb.col);
			*/
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(view.mlx_ptr, view.win_ptr, img_ptr, 0, 0);
}

int			main(int argn, char **args)
{
	t_scene	scn;
	t_view	view;

	if (argn != 2)
		return (1); //TODO: Error handling.
	scn = scn_init();
	save_conf(args[1], &scn);
	view.mlx_ptr = mlx_init();//TODO: Error hanlding plz
	view.win_ptr = mlx_new_window(view.mlx_ptr, scn.res[0], scn.res[1], "miniRT"); //TODO: Moar Error
	mlx_key_hook(view.win_ptr, &win_close, NULL);
	mlx_hook(view.win_ptr, X_CLOSE_BUTTON, 1L << 17, &quit, &view);
	fill_viewport(scn, view);
	mlx_loop(view.mlx_ptr);
	//TODO: Bad place, needs new function.
	pop_all_c(&(scn.cam));
	pop_all_l(&(scn.lgt));
	//system("leaks -quiet miniRT");
	return (0);
}
