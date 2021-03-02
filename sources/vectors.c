/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:26:36 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/02 13:37:27 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

t_coord		vect_sum(t_coord *out, t_coord v1, t_coord v2)
{
	out->x[0] = v1.x[0] + v2.x[0];
	out->x[1] = v1.x[1] + v2.x[1];
	out->x[2] = v1.x[2] + v2.x[2];
	return (*out);
}

t_coord		vect_sub(t_coord *out, t_coord v1, t_coord v2)
{
	out->x[0] = v1.x[0] - v2.x[0];
	out->x[1] = v1.x[1] - v2.x[1];
	out->x[2] = v1.x[2] - v2.x[2];
	return (*out);
}

t_coord		scalar_prod(t_coord *out, long double k, t_coord v)
{
	out->x[0] = k * v.x[0];
	out->x[1] = k * v.x[1];
	out->x[2] = k * v.x[2];
	return (*out);
}

long double	dot_prod(t_coord v1, t_coord v2)
{
	return (v1.x[0] * v2.x[0] + v1.x[1] * v2.x[1] + v1.x[2] * v2.x[2]);
}

t_coord		cross_prod(t_coord *out, t_coord v1, t_coord v2)
{
	out->x[0] = v1.x[1] * v2.x[2] - v1.x[2] * v2.x[1];
	out->x[1] = v1.x[0] * v2.x[2] - v1.x[2] * v2.x[0];
	out->x[2] = v1.x[0] * v2.x[1] - v1.x[1] * v2.x[0];
	return (*out);
}
