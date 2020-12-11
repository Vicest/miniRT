/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:50:54 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/11 11:32:47 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURES_H
# define FIGURES_H

# include "math_utils.h"
//# include "validations.h"

typedef unsigned int	t_colour;

typedef struct			s_sphere
{
	struct s_sphere		*next;
	t_coord				pos;
	t_colour			col;
	double				r;
	//colision TODO give nearest collision
}						t_sphere;

double					sphere_collision(t_sphere s, t_vector v, t_coord c);
#endif
