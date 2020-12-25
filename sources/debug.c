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

void		print_coord(t_coord p)
{
	int	i;

	printf("Coordinates:");
	i = 0;
	while (i < 3)
		printf("|%15.10Lf", p.x[i++]);
	printf("|\n");
}

void		print_vector(t_vector v)
{
	printf("Vector:");
	printf("\tOrigin ");
	print_coord(v.orig);
	printf("\tDirection ");
	print_coord(v.dir);
}

void		print_cam(t_camera cam)
{
	printf("\n----\nCamera:\n");
	printf("\tNext camera addr:%p\n", cam.next);
	print_vector(cam.vect);
	printf("\tFOV:%d\n", cam.fov);
	printf("----\n");
}

void		print_light(t_light lgt)
{
	printf("\n----\nLight:\n");
	printf("\tNext Light addr:%p\n", lgt.next);
	print_coord(lgt.pos);
	printf("\tColour:%#.8X\n", lgt.col);
	printf("Brightness:%f\n", lgt.b_ratio);
	printf("----\n");
}
void		print_scene(t_scene scn)
{
	printf("Flags:%#.2X\n", scn.flags);
	printf("Resolution (X|Y):%u|%u\n", scn.res[0], scn.res[1]);
	printf("Ambient light ratio:%lf\n",scn.amb.b_ratio);
	printf("Ambient colour RGB:%#.8X\n", scn.amb.col);
	while (scn.cam)
	{
		print_cam(*scn.cam);
		scn.cam = scn.cam->next;
	}
	while (scn.lgt)
	{
		print_light(*scn.lgt);
		scn.lgt = scn.lgt->next;
	}
	while(scn.geo)
	{
		printf("Figure addr:%p\n", scn.geo);
		printf("Next figure addr:%p\n", scn.geo->next);
		scn.geo = scn.geo->next;
	}
}
