/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:30:20 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/08 10:25:46 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H
# include "math_utils.h"
typedef unsigned int	t_colour;

typedef struct			s_camera
{
	struct s_camera		*next;
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

void		push_camera(t_camera **c_lst);
void		pop_camera(t_camera **c_lst);
void		pop_all_c(t_camera **c_lst);

void		push_light(t_light **l_lst);
void		pop_light(t_light **l_lst);
void		pop_all_l(t_light **l_lst);
#endif
