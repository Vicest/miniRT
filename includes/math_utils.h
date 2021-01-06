/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:38:53 by vicmarti          #+#    #+#             */
/*   Updated: 2021/01/06 16:48:57 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H
# include <math.h>
# include <float.h>

# define F_PREC_ERR 0.00000000005L
# define RADIANS(x) ((x) * M_PI / 180)

typedef struct			s_rota
{
	long double			azimuth;
	long double			latitude;
}						t_rota;

typedef struct			s_coord
{
	long double			x[3];
}						t_coord;

typedef struct			s_vector
{
	t_coord				orig;
	t_coord				dir;
}						t_vector;

typedef struct			s_matrix
{
	long double			m[3][3];
}						t_matrix;

long double	radians(long double degrees);

t_coord 	vector_dir(long double x, long double y, long double z);
long double	norm(t_vector v);
void		normalize(t_vector v);
void		print_vector(t_vector v);

//TODO: Solutions as a struct or something.
void		linear_solver(double a, double b, double *sol);
void		quadratic_solver(double abc[3], double *sol1, double *sol2);

t_vector	l_transform(t_matrix m, t_vector v);
t_vector	pitch(t_vector v, long double angle);
t_vector	yaw(t_vector v, long double angle);
//t_vector	roll(t_vector v, long double angle);
#endif
