/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:11:50 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/21 12:58:00 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include <stdio.h>

t_vector	pitch(t_vector v, long double angle)
{
	t_matrix	m;

	m.m[0][0] = cos(angle);
	m.m[0][1] = 0;
	m.m[0][2] = -sin(angle);
	m.m[1][0] = 0;
	m.m[1][1] = 1;
	m.m[1][2] = 0;
	m.m[2][0] = sin(angle);
	m.m[2][1] = 0;
	m.m[2][2] = cos(angle);
	return (l_transform(m, v));
}

t_vector	yaw(t_vector v,  long double angle)
{
	t_matrix	m;

	m.m[0][0] = cos(angle);
	m.m[0][1] = -sin(angle);
	m.m[0][2] = 0;
	m.m[1][0] = sin(angle);
	m.m[1][1] = cos(angle);
	m.m[1][2] = 0;
	m.m[2][0] = 0;
	m.m[2][1] = 0;
	m.m[2][2] = 1;
	return (l_transform(m, v));
}
/*
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
