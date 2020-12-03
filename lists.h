/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:30:20 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/03 10:59:20 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H
# include "math_utils.h"

typedef struct			s_camera
{
	struct s_camera		*next;
	t_coord				pos;
	t_vector			dir;
	unsigned char		fov;
}						t_camera;

void		push_camera(t_camera **c_lst, char **params);
void		pop_camera(t_camera **c_lst);
void		pop_all(t_camera **c_lst);
#endif
