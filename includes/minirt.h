/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 09:57:42 by vicmarti          #+#    #+#             */
/*   Updated: 2021/01/06 15:13:56 by vicmarti         ###   ########.fr       */
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
# ifdef __unix__
#  define KEY_ESC 0xff1b
# else
#  define KEY_ESC 53
# endif

//TODO minirt.h or a gui.h
# define X_CLOSE_BUTTON 17

# define FLAG_RES 1
# define FLAG_AMB 1 << 1

//typedef unsigned int	t_colour;
typedef unsigned	t_resolution[2];

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
	void			*mlx_ptr;
	void			*win_ptr;
	t_scene			scn;
}					t_view;

int					get_next_line(int fd, char **line);
void				save_conf(char *conf_file, t_scene *pscn);
void				store_resolution(t_scene *pscn, char **element);
void				store_ambient(t_scene *pscn, char **element);
void				store_camera(t_scene *pscn, char **element);
void				store_light(t_scene *pscn, char **element);
void				store_sphere(t_scene *pscn, char **element);

void				fill_viewport(t_view view, t_scene scn, t_camera cam);
t_vector			trace_ray(t_camera c, t_resolution r, int x, int y);
t_colour			compute_colour(t_scene scn, t_vector ray);

//TODO Gimme my own .h :'(
void				config_err(char *err_str);
#endif
