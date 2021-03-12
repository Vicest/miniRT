/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 09:57:42 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/12 21:49:57 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "../libft/libft.h"
# include "get_next_line.h"
# include "lists.h"
# include "figures.h"
# include "colours.h"
# include "math_utils.h"
# include <stdio.h>
# include <stdlib.h>

# define MAX_XRES 2560
# define MAX_YRES 1450
# define KEY_ESC 53
# define X_CLOSE_BUTTON 17
# define LARROW 0x7b
# define RARROW 0x7c
# define DARROW 0x7d
# define UARROW 0x7e
# define MV_Q 0xc
# define MV_W 0xd
# define MV_E 0xe
# define MV_A 0x0
# define MV_S 0x1
# define MV_D 0x2
# define PREV_Z 0x6
# define NEXT_X 0x7
# define SHADOW_B 0.0005
# define FLAG_RES 0x1
# define FLAG_AMB 0x10

typedef struct		s_ray
{
	t_coord			orig;
	t_coord			dir;
	t_colour		col;
}					t_ray;

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
void				store_square(t_scene *pscn, char **params, int p_num);

void				fill_viewport(t_scene scn, t_camera *pcam);
void				move_cam(t_scene scn, int kc);
void				rot_cam(t_scene scn, int kc);

int					save_bmp(t_img img, char *name, int dim[2]);
void				config_err(char *err_str);
#endif
