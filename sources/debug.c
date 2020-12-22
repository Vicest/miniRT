/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 13:08:17 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/21 12:44:02 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minirt.h"

void		print_vector(t_vector v)
{
	int	i;

	i = 0;
	while (i < 3)
		printf("|%Lf", v.v[i++]);
	printf("|\n");
}

static void	print_cams(t_scene scn)
{
	int i;

	i = 0;
	while (scn.cam)
	{
		printf("Camera:%d\n", i);
		printf("C[%d] Position:(%Lf,%Lf,%Lf)\n", i, scn.cam->pos.v[0],
				scn.cam->pos.v[1], scn.cam->pos.v[2]);
		printf("C[%d] Direction:(%Lf,%Lf,%Lf)\n", i, scn.cam->dir.v[0],
				scn.cam->dir.v[1], scn.cam->dir.v[2]);
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
		printf("L[%d] Position:(%Lf,%Lf,%Lf)\n", i, scn.lgt->pos.v[0],
				scn.lgt->pos.v[1], scn.lgt->pos.v[2]);
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
	while(scn.geo)
	{
		printf("Figure addr:%p\n", scn.geo);
		printf("Next figure addr:%p\n", scn.geo->next);
		scn.geo = scn.geo->next;
	}
}
