/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:54:06 by vicmarti          #+#    #+#             */
/*   Updated: 2021/01/22 16:58:20 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "figures.h"
#include <stdlib.h>
#include <stdio.h>

long double	plane_collision(void *plane, t_vector v)
{
	//TODO: Do some math :D
	long double	dist;
	t_plane		p;

	printf("Helllo!!\n");
	p = *(t_plane *)plane;
	dist = p.ind_term + dot_prod(v.orig, p.nvect.dir);
	dist /= dot_prod(v.dir, p.nvect.dir);
	return ((!isnan(dist) && signbit(dist) == 1 ? dist : NAN));
}

void		push_plane(t_figure **ppfig)
{
	t_figure	*aux;

	aux = malloc(sizeof(t_plane)); //TODO: Tmp Shite.
	aux->next = *ppfig;
	aux->collision = plane_collision;
	*ppfig = aux;
}
