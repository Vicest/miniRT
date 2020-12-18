/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:00:09 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/18 14:01:30 by vicmarti         ###   ########.fr       */
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
	long double		theta_step;
	double		col;

	theta_step = (long double)(scn.cam->fov * M_PI / 180.0) / (long double)scn.res[0];
	printf("Theta:%Lf\n", theta_step);
	//TODO: Do better, please, it  works weird with odd numbers.
	set_vector(&ray, 1, 0, 0);
				printf("0Ray[%lf,%lf,%lf]\n", ray.x, ray.y, ray.z);
	ray = pitch(ray, -(long double)(theta_step * scn.res[1] / 2.0));
				printf("2Ray[%lf,%lf,%lf]\n", ray.x, ray.y, ray.z);
	ray = yaw(ray, -(long double)(theta_step * scn.res[0] / 2.0));
				printf("1Ray[%lf,%lf,%lf]\n", ray.x, ray.y, ray.z);
	y = 0;
	while (y < (int)(scn.res[1]))
	{
		x = 0;
		aux = ray;
		while (x < (int)(scn.res[0]))
		{
			printf("|%Lf|%Lf|", theta_step * x, theta_step * y);
			aux = pitch(ray, theta_step * y);
			aux = yaw(aux, theta_step * x);
			col = sphere_collision(*(scn.sp), aux, scn.cam->pos);
			if (!isnan(col) && col >= 0)
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, scn.sp->col);
			else
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, scn.amb.col);
			x++;
		}
		printf("\n");
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
