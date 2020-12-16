/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 13:08:17 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/08 11:26:24 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minirt.h"

static void	print_cams(t_scene scn)
{
	int i;

	i = 0;
	while (scn.cam)
	{
		printf("Camera:%d\n", i);
		printf("C[%d] Position:(%f,%f,%f)\n", i, scn.cam->pos.x,
				scn.cam->pos.y, scn.cam->pos.z);
		printf("C[%d] Direction:(%f,%f,%f)\n", i, scn.cam->dir.x,
				scn.cam->dir.y, scn.cam->dir.z);
		printf("C[%d] FOV:%d\n", i, scn.cam->fov);
		printf("---------\n");
		scn.cam = scn.cam->next;
		i++;
	}
}

static void	print_lights(t_scene scn)
{
	int i;

	i = 0;
	while (scn.lgt)
	{
		printf("Light:%d\n", i);
		printf("L[%d] Position:(%f,%f,%f)\n", i, scn.lgt->pos.x,
				scn.lgt->pos.y, scn.lgt->pos.z);
		printf("L[%d] Colour:%#.8X\n", i, scn.lgt->col);
		printf("L[%d] Brightness:%f\n", i, scn.lgt->b_ratio);
		printf("---------\n");
		scn.lgt = scn.lgt->next;
		i++;
	}
}
void	print_scene(t_scene scn)
{
	printf("Flags:%#.2X\n", scn.flags);
	printf("Resolution (X|Y):%u|%u\n", scn.res[0], scn.res[1]);
	printf("Ambient light ratio:%lf\n",scn.amb.b_ratio);
	printf("Ambient colour RGB:%#.8X\n", scn.amb.col);
	print_cams(scn);
	print_lights(scn);
}
