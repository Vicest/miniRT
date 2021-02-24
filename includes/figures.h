/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:50:54 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/24 12:15:19 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURES_H
# define FIGURES_H

# include "math_utils.h"

typedef unsigned char	t_colour[3];

typedef struct			s_figure
{
	struct s_figure		*next;
	long double			(*collision)(void *, t_vector);
	t_vector			(*normal_at)(void *, t_coord, t_coord);
	t_colour			col;
}						t_figure;

typedef struct			s_square
{
	struct s_figure		*next;
	long double			(*collision)(void *, t_vector);
	t_vector			(*normal_at)(void *, t_coord, t_coord);
	t_colour			col;
	t_coord				side[4];
	t_coord				normal;
	long double			ind_term;
}						t_square;

typedef struct			s_triangle
{
	struct s_figure		*next;
	long double			(*collision)(void *, t_vector);
	t_vector			(*normal_at)(void *, t_coord, t_coord);
	t_colour			col;
	t_coord				vertix[3];
	t_coord				normal;
	long double			ind_term;
}						t_triangle;

typedef struct			s_plane
{
	t_figure			*next;
	long double			(*collision)(void *, t_vector);
	t_vector			(*normal_at)(void *, t_coord, t_coord);
	t_colour			col;
	t_vector			normal;
	long double			ind_term;
}						t_plane;

typedef struct			s_sphere
{
	t_figure			*next;
	long double			(*collision)(void *, t_vector);
	t_vector			(*normal_at)(void *, t_coord, t_coord);
	t_colour			col;
	t_coord				pos;
	long double			r;
}						t_sphere;

typedef struct			s_cylinder
{
	t_figure			*next;
	long double			(*collision)(void *, t_vector);
	t_vector			(*normal_at)(void *, t_coord, t_coord);
	t_colour			col;
	t_vector			pos;
	t_coord				end;
	long double			r;
	long double			h;
}						t_cylinder;

void					plane_dist(long double *d, t_vector v,
									long double iterm, t_coord n);
void					push_sphere(t_figure **ppfig);
void					push_plane(t_figure **ppfig);
void					push_cylinder(t_figure **ppfig);
void					push_triangle(t_figure **ppfig);
#endif
