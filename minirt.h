/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 09:57:42 by vicmarti          #+#    #+#             */
/*   Updated: 2020/11/25 10:32:44 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

typedef unsigned int[3] t_resolution;
typedef double[3] t_coord;
typedef double[3] t_vector;

//TODO: Maybe just better using an int? (or an array)
typedef struct	s_colour
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_colour;

typedef struct s_camera
{
	t_coord			pos;
	t_vect			dir;
	unsigned char	fov;
}				t_camera;

typedef struct	s_ambient
{
	double			ratio;
	t_colour		colour;
}				t_ambient;

typedef struct	s_scene
{
	t_resolution	res;
	t_ambient		amb;
	t_camera		cam;
	t_light			lgt;
	t_geometry		geo;
}				t_scene;
# endif
