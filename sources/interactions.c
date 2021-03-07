/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:58:14 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/07 17:58:46 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../minilibx/mlx.h"

void	move_cam(t_scene scn, int kc)
{
	t_coord		dir;
	t_coord		*pos;

	scn.at_cam->lr_dir = vector_dir(0, 1, 0);
	yaw(&scn.at_cam->lr_dir, scn.at_cam->lr_dir, scn.at_cam->rota.azimuth);
	pitch(&scn.at_cam->lr_dir, scn.at_cam->lr_dir, scn.at_cam->rota.latitude);
	scn.at_cam->ud_dir = vector_dir(0, 0, 1);
	yaw(&scn.at_cam->ud_dir, scn.at_cam->ud_dir, scn.at_cam->rota.azimuth);
	pitch(&scn.at_cam->ud_dir, scn.at_cam->ud_dir, scn.at_cam->rota.latitude);
	dir = scn.at_cam->dir;
	if (kc == MV_D || kc == MV_A)
		dir = scn.at_cam->lr_dir;
	else if (kc == MV_Q || kc == MV_E)
		dir = scn.at_cam->ud_dir;
	if (kc == MV_S || kc == MV_A || kc == MV_Q)
		scalar_prod(&dir, -2.5L, dir);
	else
		scalar_prod(&dir, 2.5L, dir);
	pos = &(scn.at_cam->orig);
	vect_sum(pos, *pos, dir);
	fill_viewport(scn, scn.at_cam);
}
