/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:11:50 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/05 15:42:24 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include <stdio.h>

t_coord		pitch(t_coord v, long double angle)
{
	t_matrix	m;

	m.m[0][0] = cosl(angle);
	m.m[0][1] = 0;
	m.m[0][2] = -sinl(angle);
	m.m[1][0] = 0;
	m.m[1][1] = 1;
	m.m[1][2] = 0;
	m.m[2][0] = sinl(angle);
	m.m[2][1] = 0;
	m.m[2][2] = cosl(angle);
	return (l_transform(m, v));
}

t_coord		yaw(t_coord v,  long double angle)
{
	t_matrix	m;

	m.m[0][0] = cosl(-angle);
	m.m[0][1] = sinl(-angle);
	m.m[0][2] = 0;
	m.m[1][0] = -sinl(-angle);
	m.m[1][1] = cosl(-angle);
	m.m[1][2] = 0;
	m.m[2][0] = 0;
	m.m[2][1] = 0;
	m.m[2][2] = 1;
	return (l_transform(m, v));
}
/* //TODO Lies
t_vector	roll(t_vector v, long double angle)
{
	t_matrix	m;

	m.m[0][0] = 1;
	m.m[0][1] = 0;
	m.m[0][2] = 0;
	m.m[1][0] = 0;
	m.m[1][1] = cos(angle);
	m.m[1][2] = -sin(angle);
	m.m[2][0] = 0;
	m.m[2][1] = sin(angle);
	m.m[2][2] = cos(angle);
	return (l_transform(m, v));
}*/
