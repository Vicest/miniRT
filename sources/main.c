/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:00:09 by vicmarti          #+#    #+#             */
/*   Updated: 2021/01/31 20:00:16 by vicmarti         ###   ########.fr       */
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
	printf("MiniRT OUT.\n");
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

static int	keypress(int keycode, t_view *pview)
{
	printf("You pressed: %#x\n", keycode);
	if (keycode == KEY_ESC)
		exit(-1); //TODO: Exit routine.
	else if (keycode == RARROW)
		pview->scn.at_cam = pview->scn.at_cam->next;
	else if (keycode == LARROW)
		pview->scn.at_cam = pview->scn.at_cam->prev;
	if (pview->scn.at_cam->img.pimg == NULL)
	{
		fill_viewport(pview->scn, pview->scn.at_cam);
	}
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
	view.scn.at_cam->img.pimg = mlx_new_image(view.mlx_ptr, view.scn.res[0], view.scn.res[1]);
		view.scn.at_cam->img.addr = mlx_get_data_addr(view.scn.at_cam->img.pimg, &view.scn.at_cam->img.bpp,
					&view.scn.at_cam->img.line_len, &view.scn.at_cam->img.endian);
	fill_viewport(view.scn, view.scn.at_cam);
	mlx_put_image_to_window(view.mlx_ptr, view.win_ptr, view.scn.at_cam->img.pimg, 0, 0);
	mlx_loop(view.mlx_ptr);
	//TODO: Bad place, needs new function.
	//pop_all_c(&(view.scn.at_cam));
	pop_all_l(&(view.scn.lgt));
	//system("leaks -quiet miniRT");
	return (0);
}
