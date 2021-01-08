/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:54:06 by vicmarti          #+#    #+#             */
/*   Updated: 2021/01/06 18:16:07 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "figures.h"
#include <stdlib.h>

long double	plane_collision(void *plane, t_vector v)
{
	//TODO: Do some math :D
	(void) plane;
	(void) v;
	return (NAN);
}

void		push_plane(t_figure **ppfig)
{
	t_figure	*aux;

	aux = malloc(sizeof(t_plane)); //TODO: Tmp Shite.
	aux->next = *ppfig;
	aux->collision = plane_collision;
	*ppfig = aux;
}