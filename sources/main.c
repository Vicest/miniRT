/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:00:09 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/07 17:58:47 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../minilibx/mlx.h"
#include <stdlib.h>

static int quit(void *params)
{
	(void)params;
	system("leaks -quiet miniRT");
	exit(-1);
	return (1);
}

static int	keypress(int kc, t_view *pv)
{
	if (kc == KEY_ESC)
		exit(-1); //TODO: Exit routine.
	else if (kc == NEXT_X)
		pv->scn.at_cam = pv->scn.at_cam->next;
	else if (kc == PREV_Z)
		pv->scn.at_cam = pv->scn.at_cam->prev;
	else if (kc == MV_W || kc == MV_A || kc == MV_S || kc == MV_D || kc == MV_Q || kc == MV_E)
		move_cam(pv->scn, kc);
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
	return (0);
}

static void	mlx_setup(t_view *pv)
{
	//TODO: Error hanlding plz
	pv->pmlx = mlx_init();
	//TODO: Moar Error
	//mlx_get_screen_size(pv->pmlx, &pv->scn.res[0], &pv->scn.res[1]);
	pv->pwin = mlx_new_window(pv->pmlx, pv->scn.res[0], pv->scn.res[1], "myRT");
	mlx_key_hook(pv->pwin, &keypress, pv);
	mlx_hook(pv->pwin, X_CLOSE_BUTTON, 1L << 17, &quit, &pv);
	pv->scn.at_cam->img.pimg = mlx_new_image(
				pv->pmlx, pv->scn.res[0], pv->scn.res[1]);
	pv->scn.at_cam->img.addr = mlx_get_data_addr(
				pv->scn.at_cam->img.pimg, &pv->scn.at_cam->img.bpp,
				&pv->scn.at_cam->img.line_len, &pv->scn.at_cam->img.endian);
}

int			main(int argn, char **args)
{
	t_view	view;

	if (!(argn == 2 || (argn == 3 && ft_strcmp(args[2], "--save") == 0)))
		config_err("Invalid number of parameters.\n");
	ft_memset(&view, 0, sizeof(t_view));
	save_conf(args[1], &view.scn);
	mlx_setup(&view);
	fill_viewport(view.scn, view.scn.at_cam);
	if (argn == 3)
		return (save_bmp(view.scn.at_cam->img, args[1], view.scn.res));
	mlx_put_image_to_window(view.pmlx, view.pwin,
							view.scn.at_cam->img.pimg, 0, 0);
	mlx_loop(view.pmlx);
	//TODO: Bad place, needs new function.
	//pop_all_c(&(view.scn.at_cam));
	pop_all_l(&(view.scn.lgt));
	system("leaks -quiet miniRT");
	return (0);
}
