/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 13:08:17 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/07 13:48:16 by vicmarti         ###   ########.fr       */
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
		printf("C[%d] Position:(%f,%f,%f)\n", i, scn.cam->pos[0],
				scn.cam->pos[1], scn.cam->pos[2]);
		printf("C[%d] Direction:(%f,%f,%f)\n", i, scn.cam->dir[0],
				scn.cam->dir[1], scn.cam->dir[2]);
		printf("C[%d] FOV:%d\n", i, scn.cam->fov);
		printf("---------\n");
		scn.cam = scn.cam->next;
		i++;
	}
}

void	print_scene(t_scene scn)
{
	printf("Flags:%#.2X\n", scn.flags);
	printf("Resolution (X|Y):%u|%u\n", scn.res[0], scn.res[1]);
	printf("Ambient light ratio:%lf\n",scn.amb.ratio);
	printf("Ambient colour RGB:%#.8X\n", scn.amb.col);
	print_cams(scn);
}
