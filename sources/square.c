/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:24:22 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/10 15:23:11 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "figures.h"
#include <stdlib.h>

long double	square_collision(void *square, t_coord orig, t_coord dir)
{
	t_square	s;
	t_coord		p;
	long double	dist;

	s = *(t_square *)square;
	dist = s.ind_term - dot_prod(orig, s.normal);
	dist /= dot_prod(dir, s.normal);
	if (isnan(dist) || isinf(dist) || dist < 1)
		dist = NAN;
	p = move_p(orig, dir, dist);
	if (!inside_check(p, s.normal, s.vertix, 4))
		return (NAN);
	return (dist);
}

t_coord		square_normal(void *square, t_coord at, t_coord facing)
{
	t_coord		normal;

	normal = ((t_square *)square)->normal;
	vect_sub(&facing, facing, at);
	if (dot_prod(normal, facing) < 0)
		scalar_prod(&normal, -1.0L, normal);
	return (normal);
}

void		push_square(t_figure **ppfig)
{
	t_figure	*aux;

	if (!(aux = malloc(sizeof(t_square))))
		config_err("Could not allocate mem.\n");
	aux->next = *ppfig;
	aux->collision = square_collision;
	aux->normal_at = square_normal;
	*ppfig = aux;
}
