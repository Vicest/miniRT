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

# include "minirt.h"
# include "math_utils.h"
//# include "validations.h"

typedef unsigned int	t_colour;

typedef struct			s_sphere
{
	void				*next;
	t_coord				pos;
	t_colour			col;
	double				r;
	double				*collision(void *,t_vector, t_coord);
}						t_sphere;

void					push_sphere(t_scene *pscn);
double					sphere_collision(void *sphere, t_vector v, t_coord c);
#endif
