/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:50:54 by vicmarti          #+#    #+#             */
/*   Updated: 2021/01/06 15:20:26 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURES_H
# define FIGURES_H

# include "math_utils.h"

typedef unsigned int	t_colour;

typedef struct			s_figure
{
	struct s_figure		*next;
	long double			(*collision)(void *,t_vector);
	t_colour			col;
}						t_figure;

typedef struct			s_plane
{
	t_figure			*next;
	t_vector			nvect;
}						t_plane;

typedef struct			s_sphere
{
	t_figure			*next;
	t_coord				pos;
	t_colour			col;
	double				r;
	long double			(*collision)(void *,t_vector);
}						t_sphere;

void					push_sphere(t_figure *pscn);
long double				sphere_collision(void *sphere, t_vector v);
void					push_plane(t_figure *pscn);
long double				plane_collision(void *plane, t_vector v);
#endif
