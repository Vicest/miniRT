/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:54:06 by vicmarti          #+#    #+#             */
/*   Updated: 2021/01/29 14:10:11 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "figures.h"
#include <stdlib.h>
#include <stdio.h>

long double	plane_collision(void *plane, t_vector v)
{
	long double	dist;
	t_plane		p;

	p = *(t_plane *)plane;
	dist = p.ind_term - dot_prod(v.orig, p.nvect.dir);
	dist /= dot_prod(v.dir, p.nvect.dir);
	//TODO: Look at the signbit method, maybe I don't need isnan.
	return ((!isnan(dist) && signbit(dist) == 0 ? dist : NAN));
}

void		push_plane(t_figure **ppfig)
{
	t_figure	*aux;

	aux = malloc(sizeof(t_plane)); //TODO: Tmp Shite.
	aux->next = *ppfig;
	aux->collision = plane_collision;
	*ppfig = aux;
}
