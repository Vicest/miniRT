/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:38:53 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/18 13:34:30 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H
# include <math.h>
# include <float.h>

# define RADIANS(x) (x * M_PI / 180)

typedef struct			s_vector
{
	double				x;
	double				y;
	double				z;
}						t_vector;

typedef struct			s_matrix
{
	t_vector			x;
	t_vector			y;
	t_vector			z;
}						t_matrix;

typedef t_vector		t_coord;

void		set_vector(t_vector *v, double x, double y, double z);
int			is_normal(t_vector v);
void		linear_solver(double a, double b, double *sol);
void		quadratic_solver(double abc[3], double *sol1, double *sol2);
t_vector	l_transform(t_matrix m, t_vector v);
t_vector	pitch(t_vector v, long double angle);
t_vector	roll(t_vector v, long double angle);
t_vector	yaw(t_vector v, long double angle);
#endif
