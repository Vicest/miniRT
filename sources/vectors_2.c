/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:31:50 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/07 18:00:54 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

t_coord		point_at_dist(t_coord orig, t_coord dir, long double dist)
{
	t_coord		point;
	int			i;

	i = -1;
	while (++i < 3)
		point.x[i] = dist * dir.x[i] + orig.x[i];
	return (point);
}

long double	norm(t_coord v)
{
	return (sqrt(dot_prod(v, v)));
}

int			is_normalized(t_coord v)
{
	return (equals_zero(fabsl(1 - norm(v))));
}

void		normalize(t_coord *v)
{
	long double	inv_norm;

	inv_norm = 1.0L / norm(*v);
	v->x[0] *= inv_norm;
	v->x[1] *= inv_norm;
	v->x[2] *= inv_norm;
}

t_coord		vector_dir(long double x, long double y, long double z)
{
	t_coord		dir;

	dir.x[0] = x;
	dir.x[1] = y;
	dir.x[2] = z;
	return (dir);
}
