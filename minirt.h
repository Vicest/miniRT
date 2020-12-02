/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 09:57:42 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/02 14:06:50 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
//# include "error.h"
# include "libft/libft.h"
# include "get_next_line.h"
# include "math_utils.h"
# include "lists.h"
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define N_IDS 9
# define MAX_XRES 1024
# define MAX_YRES 860

# define FLAG_RES 1
# define FLAG_AMB 1 << 1

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

typedef unsigned int	t_resolution[2];
typedef unsigned char	t_colour[3];

typedef struct			s_light
{
	struct s_light	*next;
	t_coord			pos;
	t_colour		col;
	double			ratio;
}						t_light;

typedef struct			s_ambient
{
	double			ratio;
	t_colour		col;
}						t_ambient;

typedef struct			s_scene
{
	char			flags;
	t_resolution	res;
	t_ambient		amb;
	t_camera		*cam;
//	t_light			*lgt;
//	t_geometry		geo;
}						t_scene;

int						get_next_line(int fd, char **line);
void					save_conf(char *conf_file, t_scene *pscn);
void					store_resolution(t_scene *pscn, char **element);
void					store_ambient(t_scene *pscn, char **element);
void					store_camera(t_scene *pscn, char **element);
#endif
