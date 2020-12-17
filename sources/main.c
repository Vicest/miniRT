/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:00:09 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/15 14:48:52 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../minilibx/mlx.h"
#include <stdlib.h>

#define X_CLOSE_BUTTON 17


static int	win_close(int keycode)
{
	if (keycode == 53)
	{
		//system("leaks -quiet miniRT");
		exit(-1);
	}
	else
		printf("nope\n");
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

void		initialize(t_scene *scn)
{
	scn->flags = 0;
	scn->res[0] = 0;
	scn->res[1] = 0;
	scn->amb.b_ratio = 0;
	scn->amb.col = 0;
	scn->cam = NULL;
	scn->lgt = NULL;
	scn->sp = NULL;
}

void		fill_viewport(t_scene scn, void *mlx_ptr, void *win_ptr)
{
	int			x;
	int			y;
	t_vector	ray;
	t_vector	aux;
	double		horizontal_step;
	double		vertical_step;
	double		col;

	horizontal_step = (double)scn.cam->fov / (double)scn.res[0];
	horizontal_step *= M_PI / 180;
	vertical_step = (double)scn.cam->fov / (double)scn.res[1];
	vertical_step *= M_PI / 180;
	printf("ThetaH:%f\n", horizontal_step);
	printf("ThetaV:%f\n", vertical_step);
	//TODO: Do better, please, it  works weird with odd numbers.
	set_vector(&ray, 1, 0, 0);
	ray = yaw(ray, -(double)(M_PI * scn.cam->fov / 360.0));
	ray = pitch(ray, -(double)(M_PI * scn.cam->fov / 360.0));
	y = 0;
	while (y < (int)(scn.res[1]))
	{
		x = 0;
		while (x < (int)(scn.res[0]))
		{
			aux = yaw(ray, horizontal_step * x);
			//printf("Ray[%lf,%lf,%lf]\n", aux[0], aux[1], aux[2]);
			/*
			ray[0] = cos(theta_step * y) * cos(-scn.cam->fov/2.0 + theta_step * x);
			ray[1] = sin(-scn.cam->fov/2.0 + theta_step * x);
			ray[2] = sin(theta_step * y) * cos(-scn.cam->fov/2.0 + theta_step * x);
			*/
			col = sphere_collision(*(scn.sp), aux, scn.cam->pos);
			if (!isnan(col) && col >= 0)
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, scn.sp->col);
			else
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, scn.amb.col);
			x++;
		}
		ray = pitch(ray, vertical_step);
		y++;
	}
}

int			main(int argn, char **args)
{
	t_scene	scn;
	t_view	view;

	if (argn != 2)
		return (1); //TODO: Error handling.
	initialize(&scn);
	save_conf(args[1], &scn);
	view.mlx_ptr = mlx_init();//TODO: Error hanlding plz
	view.win_ptr = mlx_new_window(view.mlx_ptr, scn.res[0], scn.res[1], "miniRT"); //TODO: Moar Error
	mlx_key_hook(view.win_ptr, &win_close, NULL);
	mlx_hook(view.win_ptr, X_CLOSE_BUTTON, 1L << 17, &quit, &view);
	printf("----\n");
	fill_viewport(scn, view.mlx_ptr, view.win_ptr);
	printf("----\n");
	mlx_loop(view.mlx_ptr);
	//TODO: Bad place, needs new function.
	pop_all_c(&(scn.cam));
	pop_all_l(&(scn.lgt));
	//system("leaks -quiet miniRT");
	return (0);
}
