/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 09:57:42 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/28 20:38:53 by vicmarti         ###   ########.fr       */
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
#  define UARROW 0xff52
#  define RARROW 0xff53
#  define DARROW 0xff54
#  define MV_Q 0x71
#  define MV_W 0x77
#  define MV_E 0x65
#  define MV_A 0x61
#  define MV_S 0x73
#  define MV_D 0x64
#  define PREV_Z 0x7a
#  define NEXT_X 0x78
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

# define SHADOW_B 0.0005L
# define FLAG_RES 1
# define FLAG_AMB 1 << 1

typedef struct		s_scene
{
	char			flags;
	int				res[2];
	t_colour		amb;
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
void				store_resolution(t_scene *pscn, char **params, int p_num);
void				store_ambient(t_scene *pscn, char **params, int p_num);
void				store_camera(t_scene *pscn, char **params, int p_num);
void				store_light(t_scene *pscn, char **params, int p_num);
void				store_sphere(t_scene *pscn, char **params, int p_num);
void				store_plane(t_scene *pscn, char **params, int p_num);
void				store_cylinder(t_scene *pscn, char **params, int p_num);
void				store_triangle(t_scene *pscn, char **params, int p_num);

void				fill_viewport(t_scene scn, t_camera *pcam);
//t_colour			compute_colour(t_scene scn, t_vector ray);

int			save_bmp(t_img img, char *name, int dim[2]);
//TODO Gimme my own .h :'(
void				config_err(char *err_str);
#endif
