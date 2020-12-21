/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:38:53 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/21 13:34:08 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H
# include <math.h>
# include <float.h>

# define RADIANS(x) ((x) * M_PI / 180)
# define NORM(x) (sqrt(pow((x).v[0], 2) + pow((x).v[1], 2) + pow((x).v[2], 2)))
//TODO: Equals is too strict as a float comparison.
//https://github.com/brazzy/floating-point-gui.define
//geeksforgeeks.com/(something something about corrctly compare floats
# define IS_NORMALIZED(x) (1 == NORM((x)))

//TODO: Redo this in favour of the more iterable-friendly method.

typedef struct			s_vector
{
	long double			v[3];
}						t_vector;

typedef t_vector		t_coord;

typedef struct			s_matrix
{
	t_vector			m[3];
}						t_matrix;

long double	radians(long double degrees);
t_vector 	vector(long double x, long double y, long double z);
void		normalize(t_vector *v);
//TODO: Solutions as a struct or something.
void		linear_solver(double a, double b, double *sol);
void		quadratic_solver(double abc[3], double *sol1, double *sol2);
//t_vector	l_transform(t_matrix m, t_vector v);
//t_vector	pitch(t_vector v, long double angle);
//t_vector	roll(t_vector v, long double angle);
//t_vector	yaw(t_vector v, long double angle);
#endif
