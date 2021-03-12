/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:50:54 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/12 21:46:28 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURES_H
# define FIGURES_H

# include "math_utils.h"

typedef unsigned char	t_colour[3];

typedef struct			s_figure
{
	struct s_figure		*next;
	long double			(*collision)(void *, t_coord, t_coord);
	t_coord				(*normal_at)(void *, t_coord, t_coord);
	t_colour			col;
}						t_figure;

typedef struct			s_square
{
	struct s_figure		*next;
	long double			(*collision)(void *, t_coord, t_coord);
	t_coord				(*normal_at)(void *, t_coord, t_coord);
	t_colour			col;
	t_coord				centre;
	t_coord				normal;
	t_coord				vertix[4];
	long double			ind_term;
}						t_square;

typedef struct			s_triangle
{
	struct s_figure		*next;
	long double			(*collision)(void *, t_coord, t_coord);
	t_coord				(*normal_at)(void *, t_coord, t_coord);
	t_colour			col;
	t_coord				vertix[3];
	t_coord				normal;
	long double			ind_term;
}						t_triangle;

typedef struct			s_plane
{
	t_figure			*next;
	long double			(*collision)(void *, t_coord, t_coord);
	t_coord				(*normal_at)(void *, t_coord, t_coord);
	t_colour			col;
	t_coord				centre;
	t_coord				normal;
	long double			ind_term;
}						t_plane;

typedef struct			s_sphere
{
	t_figure			*next;
	long double			(*collision)(void *, t_coord, t_coord);
	t_coord				(*normal_at)(void *, t_coord, t_coord);
	t_colour			col;
	t_coord				pos;
	long double			r;
}						t_sphere;

typedef struct			s_cylinder
{
	t_figure			*next;
	long double			(*collision)(void *, t_coord, t_coord);
	t_coord				(*normal_at)(void *, t_coord, t_coord);
	t_colour			col;
	t_coord				orig;
	t_coord				dir;
	t_coord				end;
	long double			r;
	long double			h;
}						t_cylinder;

int						inside_check(t_coord p, t_coord nv, t_coord *vertix,
									int v_num);
void					push_sphere(t_figure **ppfig);
void					push_plane(t_figure **ppfig);
void					push_cylinder(t_figure **ppfig);
void					push_triangle(t_figure **ppfig);
void					push_square(t_figure **ppfig);
#endif
