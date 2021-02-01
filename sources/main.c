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

static int	keypress(int keycode, t_view *pv)
{
	printf("You pressed: %#x\n", keycode);
	if (keycode == KEY_ESC)
		exit(-1); //TODO: Exit routine.
	else if (keycode == RARROW)
		pv->scn.at_cam = pv->scn.at_cam->next;
	else if (keycode == LARROW)
		pv->scn.at_cam = pv->scn.at_cam->prev;
	if (pv->scn.at_cam->img.pimg == NULL)
	{
		pv->scn.at_cam->img.pimg = mlx_new_image(
					pv->pmlx, pv->scn.res[0], pv->scn.res[1]);
		pv->scn.at_cam->img.addr = mlx_get_data_addr(
					pv->scn.at_cam->img.pimg, &pv->scn.at_cam->img.bpp,
					&pv->scn.at_cam->img.line_len, &pv->scn.at_cam->img.endian);
		fill_viewport(pv->scn, pv->scn.at_cam);
	}
	mlx_put_image_to_window(pv->pmlx, pv->pwin,
					pv->scn.at_cam->img.pimg, 0, 0);
	return (-1);
	//mlx_destroy_window(mlx_ptr, win_ptr);
}

static void	mlx_setup(t_view *pv)
{
	//TODO: Error hanlding plz
	pv->pmlx = mlx_init();
	//TODO: Moar Error
	pv->pwin = mlx_new_window(pv->pmlx, pv->scn.res[0], pv->scn.res[1], "myRT");
	mlx_key_hook(pv->pwin, &keypress, pv);
	mlx_hook(pv->pwin, X_CLOSE_BUTTON, 1L << 17, &quit, &pv);
	pv->scn.at_cam->img.pimg = mlx_new_image(
				pv->pmlx, pv->scn.res[0], pv->scn.res[1]);
	pv->scn.at_cam->img.addr = mlx_get_data_addr(
				pv->scn.at_cam->img.pimg, &pv->scn.at_cam->img.bpp,
				&pv->scn.at_cam->img.line_len, &pv->scn.at_cam->img.endian);
	fill_viewport(pv->scn, pv->scn.at_cam);
	mlx_put_image_to_window(pv->pmlx, pv->pwin, pv->scn.at_cam->img.pimg, 0, 0);
}

int			main(int argn, char **args)
{
	t_view	view;

	if (argn != 2)
		return (1); //TODO: Error handling.
	view.scn = scn_init();
	save_conf(args[1], &view.scn);
	mlx_setup(&view);
	mlx_loop(view.pmlx);
	//TODO: Bad place, needs new function.
	//pop_all_c(&(view.scn.at_cam));
	pop_all_l(&(view.scn.lgt));
	//system("leaks -quiet miniRT");
	return (0);
}
