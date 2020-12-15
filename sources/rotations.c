/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:11:50 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/15 13:26:00 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

void	pitch(t_vector v, double angle, t_vector *rot)
{
	t_matrix	m;

	m[0][0] = cos(angle);
	m[0][1] = 0;
	m[0][2] = -sin(angle);
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[2][0] = sin(angle);
	m[2][1] = 0;
	m[2][2] = cos(angle);
	l_transform(m, v, rot);
}
void	yaw(t_vector v, double angle, t_vector *rot)
{
	t_matrix	m;

	m[0][0] = cos(angle);
	m[0][1] = -sin(angle);
	m[0][2] = 0;
	m[1][0] = sin(angle);
	m[1][1] = cos(angle);
	m[1][2] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	l_transform(m, v, rot);
}

void	roll(t_vector v, double angle, t_vector *rot)
{
	t_matrix	m;

	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[1][0] = 0;//cos(angle);
	m[1][1] = cos(angle);
	m[1][2] = -sin(angle);
	m[2][0] = 0;
	m[2][1] = sin(angle);
	m[2][2] = cos(angle);
	l_transform(m, v, rot);
}
