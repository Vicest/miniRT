/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:50:54 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/20 12:26:16 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURES_H
# define FIGURES_H

# include "math_utils.h"
//# include "validations.h"

typedef unsigned int	t_colour;

typedef struct			s_figure
{
	struct s_figure		*next;
	long double			(*collision)(void *,t_vector);
	t_colour			col;
}						t_figure;

typedef struct			s_sphere
{
	struct s_sphere		*next;
	t_coord				pos;
	t_colour			col;
	double				r;
	long double			(*collision)(void *,t_vector);
}						t_sphere;

long double				sphere_collision(void *sphere, t_vector v);
#endif
