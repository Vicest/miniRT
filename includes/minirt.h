/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 09:57:42 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/04 14:16:56 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
//# include "error.h"
# include "../libft/libft.h"
# include "get_next_line.h"
# include "lists.h"
# include "figures.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MAX_XRES 4096
# define MAX_YRES 4096
//TODO minirt.h or a gui.h
# ifdef __unix__
#  define KEY_ESC 0xff1b
#  define X_CLOSE_BUTTON 17//TODO Definitely wrong!(?)
#  define LARROW 0xff51
#  define RARROW 0xff53
#  define MV_Q 0x71
#  define MV_W 0x77
#  define MV_E 0x65
#  define MV_A 0x61
#  define MV_S 0x73
#  define MV_D 0x64
# else
#  define KEY_ESC 53
#  define X_CLOSE_BUTTON 17
#  define LARROW 0x7b
#  define RARROW 0x7c
#  define DARROW 0x7d
#  define UARROW 0x7e
#  define MV_Q 0xc
#  define MV_W 0xd
#  define MV_E 0xe
#  define MV_A 0x0
#  define MV_S 0x1
#  define MV_D 0x2
#  define PREV_Z 0x6
#  define NEXT_X 0x7
# endif


# define FLAG_RES 1
# define FLAG_AMB 1 << 1

//typedef unsigned int	t_colour;
typedef int			t_resolution[2];

typedef struct		s_ambient
{
	double			b_ratio;
	t_colour		col;
}					t_ambient;

typedef struct		s_scene
{
	char			flags;
	t_resolution	res;
	t_ambient		amb;
	t_camera		*at_cam;
	t_light			*lgt;
	t_figure		*geo;
}					t_scene;

typedef struct		s_view
{
	void			*pmlx;
	void			*pwin;
	t_scene			scn;
}					t_view;

int					get_next_line(int fd, char **line);
void				save_conf(char *conf_file, t_scene *pscn);
void				store_resolution(t_scene *pscn, char **element);
void				store_ambient(t_scene *pscn, char **element);
void				store_camera(t_scene *pscn, char **element);
void				store_light(t_scene *pscn, char **element);
void				store_sphere(t_scene *pscn, char **element);
void				store_plane(t_scene *pscn, char **element);

void				fill_viewport(t_scene scn, t_camera *pcam);
//t_colour			compute_colour(t_scene scn, t_vector ray);

//TODO Gimme my own .h :'(
void				config_err(char *err_str);
#endif
