/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:30:20 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/09 12:49:17 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H
# include "math_utils.h"
typedef unsigned		t_colour;

typedef struct			s_geometry
{
	struct s_geometry	*next;
	void				*figure;
}						t_geometry;

typedef struct			s_img
{
	void				*pimg;
	void				*canv;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_img;

typedef struct			s_camera
{
	struct s_camera		*next;
	t_img				img;
	t_coord				pos;
	t_vector			dir;
	unsigned char		fov;
}						t_camera;

typedef struct			s_light
{
	struct s_light		*next;
	t_coord				pos;
	t_colour			col;
	double				b_ratio;
}						t_light;

void					push_camera(t_camera **c_lst);
void					pop_camera(t_camera **c_lst);
void					pop_all_c(t_camera **c_lst);

void		push_light(t_light **l_lst);
void		pop_light(t_light **l_lst);
void		pop_all_l(t_light **l_lst);
#endif
