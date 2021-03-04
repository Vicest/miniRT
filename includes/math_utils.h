/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:38:53 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/04 14:51:20 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H
# include <math.h>
# include <float.h>

# define EPSILON 0.0000005L

typedef struct			s_rota
{
	long double			azimuth;
	long double			latitude;
}						t_rota;

typedef struct			s_coord
{
	long double			x[3];
}						t_coord;

typedef struct			s_matrix
{
	long double			m[3][3];
}						t_matrix;

long double	radians(long double degrees);
int			equals_zero(long double l);

t_coord 	vector_dir(long double x, long double y, long double z);
t_coord		vect_sum(t_coord *out, t_coord v1, t_coord v2);
t_coord		vect_sub(t_coord *out, t_coord v1, t_coord v2);
t_coord		scalar_prod(t_coord *out, long double k, t_coord v);
long double	dot_prod(t_coord v1, t_coord v2);
t_coord		cross_prod(t_coord *out, t_coord v1, t_coord v2);
long double	norm(t_coord v);
void		normalize(t_coord *v);
int			is_normalized(t_coord v);
t_coord		point_at_dist(t_coord orig, t_coord dir, long double dist);

//TODO: Solutions as a struct or something.
void		linear_solve(long double a, long double b, long double *sol);
void		quad_solve(long double abc[3], long double *sol1, long double *sol2);

t_coord		l_transform(t_matrix m, t_coord v);

t_rota		inv_spherical(t_coord v);
t_coord		pitch(t_coord v, long double angle);
t_coord		yaw(t_coord v, long double angle);
//t_vector	roll(t_vector v, long double angle);
#endif
