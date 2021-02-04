/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:00:09 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/03 14:54:41 by vicmarti         ###   ########.fr       */
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

static void	move_cam(t_scene scn, int kc)
{
	t_coord		dir;
	t_coord		*pos;

	printf("I'm in\n");
	pos = &(scn.at_cam->vect.orig);
	dir = scn.at_cam->vect.dir;
	if (kc == MV_D || kc == MV_A)
		dir = scn.at_cam->lr_dir;
	else if (kc == MV_Q || kc == MV_E)
		dir = scn.at_cam->ud_dir;
	if (kc == MV_S || kc == MV_A || kc == MV_Q)
		scalar_prod(&dir, -1.0L, dir);
	printf("Pre\n");
	print_coord(*pos);
	printf("Dir\n");
	print_coord(dir);
	vect_sum(pos, *pos, dir);
	printf("Post\n");
	print_coord(*pos);
	fill_viewport(scn, scn.at_cam);
}

static int	keypress(int kc, t_view *pv)
{
	printf("You pressed: %#x\n", kc);
	if (kc == KEY_ESC)
		exit(-1); //TODO: Exit routine.
	else if (kc == RARROW)
		pv->scn.at_cam = pv->scn.at_cam->next;
	else if (kc == LARROW)
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
	ft_memset(&view, 0, sizeof(t_view));
	save_conf(args[1], &view.scn);
	mlx_setup(&view);
	mlx_loop(view.pmlx);
	//TODO: Bad place, needs new function.
	//pop_all_c(&(view.scn.at_cam));
	pop_all_l(&(view.scn.lgt));
	//system("leaks -quiet miniRT");
	return (0);
}
