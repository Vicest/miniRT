/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 09:57:42 by vicmarti          #+#    #+#             */
/*   Updated: 2020/11/27 10:35:51 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "error.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_res
{
	unsigned int	x;
	unsigned int	x;
}				t_res;

//TODO: Maybe just better using an int? (or an array)
typedef struct	s_colour
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_colour

typedef double[3] t_coord;
typedef double[3] t_vector;

typedef struct t_camera
{
	t_coord			pos;
	t_vect			dir;
	unsigned char	fov;

typedef struct	s_ambient
{
	double			ratio;
	t_colour		colour;
}				t_ambient

typedef struct	s_scn
{
	t_resolution	res;
	t_ambient		amb;
	t_camera		cam;
	t_light			lgt;
	t_geometry		geo;
}				t_scene;
# endif
