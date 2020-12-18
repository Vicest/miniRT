/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:11:50 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/18 14:02:13 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include <stdio.h>

t_vector	pitch(t_vector v, long double angle)
{
	t_matrix	m;

	m.x.x = cos(angle);
	m.x.y = 0;
	m.x.z = -sin(angle);
	m.y.x = 0;
	m.y.y = 1;
	m.y.z = 0;
	m.z.x = sin(angle);
	m.z.y = 0;
	m.z.z = cos(angle);
	return (l_transform(m, v));
}
t_vector	yaw(t_vector v,  long double angle)
{
	t_matrix	m;

	m.x.x = cos(angle);
	m.x.y = -sin(angle);
	m.x.z = 0;
	m.y.x = sin(angle);
	m.y.y = cos(angle);
	m.y.z = 0;
	m.z.x = 0;
	m.z.y = 0;
	m.z.z = 1;
/*
	printf("Vector\n[%lf][%lf][%lf]\n",v.x,v.y,v.z);
	printf("Matrix\n[%lf][%lf][%lf]\n",m.x.x,m.x.y,m.x.z);
	printf("[%lf][%lf][%lf]\n",m.y.x,m.y.y,m.y.z);
	printf("[%lf][%lf][%lf]\n",m.z.x,m.z.y,m.z.z);
	*/
	
	return (l_transform(m, v));
}

t_vector	roll(t_vector v, long double angle)
{
	t_matrix	m;

	m.x.x = 1;
	m.x.y = 0;
	m.x.z = 0;
	m.y.x = 0;
	m.y.y = cos(angle);
	m.y.z = -sin(angle);
	m.z.x = 0;
	m.z.y = sin(angle);
	m.z.z = cos(angle);
	return (l_transform(m, v));
}
