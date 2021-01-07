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
#include "debug.h"
#include "../minilibx/mlx.h"
#include <stdlib.h>

static int quit(void *params)
{
	(void)params;
	//system("leaks -quiet miniRT");
	printf("Lolailo\n");
	exit(-1);
	return (1);
}

//TODO: Initializers with calloc.

static t_scene	scn_init()
{
	t_scene scn;

	scn.flags = 0;
	scn.res[0] = 0;
	scn.res[1] = 0;
	scn.amb.b_ratio = 0;
	scn.amb.col = 0;
	scn.at_cam = NULL;
	scn.lgt = NULL;
	scn.geo = NULL;

	return (scn);
}


void		fill_viewport(t_view view, t_scene scn, t_camera *pcam)
{
	int			x;
	int			y;
	t_vector	ray;
	t_colour	col;

	//printf("----\nMy cam%p\n----\n", &cam);
	//print_cam(cam);
	pcam->img.pimg = mlx_new_image(view.mlx_ptr, scn.res[0], scn.res[1]);
	pcam->img.addr = mlx_get_data_addr(pcam->img.pimg, &pcam->img.bpp,
				&pcam->img.line_len, &pcam->img.endian);
	y = 0;
	printf("Fillvp cam:");
	print_cam(*pcam);
	while (y < (int)(scn.res[1]))
	{
		x = 0;
		while (x < (int)(scn.res[0]))
		{
			ray = trace_ray(*pcam, scn.res, x, y);
			/*
			if (x == y && x == 0)
			{
				printf("Fillvp ray:");
				print_vector(ray);
			}*/
			col = compute_colour(scn, ray);
			*(unsigned *)(pcam->img.addr + x * (pcam->img.bpp / 8) +
				y * pcam->img.line_len) = col;
			x++;
		}
		y++;
	}
	//TODO: Out of this function.
	mlx_put_image_to_window(view.mlx_ptr, view.win_ptr, pcam->img.pimg, 0, 0);
}

static int	keypress(int keycode, t_view *pview)
{
	printf("You pressed: %#x\n", keycode);
	if (keycode == KEY_ESC)
		exit(-1); //TODO: Exit routine.
	else if (keycode == 0xff53) //TODO: Macro it to ->
	{
		printf("NextCam\n");
		pview->scn.at_cam = pview->scn.at_cam->next;
	}
	else if (keycode == 0xff51) //TODO: Macro it to <-
	{
		printf("PrevCam\n");
		pview->scn.at_cam = pview->scn.at_cam->prev;
	}
	if (pview->scn.at_cam->img.pimg == NULL)
	{
		printf("Fillin' it\n");
		fill_viewport(*pview, pview->scn, pview->scn.at_cam);
	}
	else
		mlx_put_image_to_window(pview->mlx_ptr, pview->win_ptr, pview->scn.at_cam->img.pimg, 0, 0);
	return (-1);
	//mlx_destroy_window(mlx_ptr, win_ptr);
}

int			main(int argn, char **args)
{
	t_view	view;

	if (argn != 2)
		return (1); //TODO: Error handling.
	view.scn = scn_init();
	save_conf(args[1], &view.scn);
	view.mlx_ptr = mlx_init();//TODO: Error hanlding plz
	view.win_ptr = mlx_new_window(view.mlx_ptr, view.scn.res[0], view.scn.res[1], "miniRT"); //TODO: Moar Error
	mlx_key_hook(view.win_ptr, &keypress, &view);
	mlx_hook(view.win_ptr, X_CLOSE_BUTTON, 1L << 17, &quit, &view);
	fill_viewport(view, view.scn, view.scn.at_cam);
	mlx_loop(view.mlx_ptr);
	//TODO: Bad place, needs new function.
	//pop_all_c(&(view.scn.at_cam));
	pop_all_l(&(view.scn.lgt));
	//system("leaks -quiet miniRT");
	return (0);
}
