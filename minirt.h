/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 09:57:42 by vicmarti          #+#    #+#             */
/*   Updated: 2020/11/25 12:57:21 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define N_IDS 9

//# define IDENTIFIERS "R,A,c,l,sp,pl,sq,cy,tr"

static char				g_identifiers[N_IDS + 1][3] = {
						"R",
						"A",
						"l",
						"c",
						"sp",
						"pl",
						"sq",
						"cy",
						"tr",
						{'\0'}
};

typedef unsigned int	t_resolution[3];
typedef double			t_vector[3];
typedef double			t_coord[3];

//TODO: Maybe just better using an int? (or an array)
typedef struct			s_colour
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}						t_colour;

typedef struct			s_light
{
	t_coord		pos;
	t_colour	col;
	double		ratio;
}						t_light;

typedef struct			s_camera
{
	t_coord			pos;
	t_vector		dir;
	unsigned char	fov;
}						t_camera;

typedef struct			s_ambient
{
	double			ratio;
	t_colour		col;
}						t_ambient;

typedef struct			s_scene
{
	t_resolution	res;
	t_ambient		amb;
	t_camera		cam;
	t_light			lgt;
//	t_geometry		geo;
}						t_scene;

int						get_next_line(int fd, char **line);
#endif
