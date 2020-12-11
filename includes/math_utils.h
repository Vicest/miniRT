/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:38:53 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/11 11:24:04 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H
# include <math.h>
# include <float.h>

typedef double			t_vector[3];
typedef double			t_coord[3];

int			is_normal(t_vector v);
void		linear_solver(double a, double b, double sol);
void		quadratic_solver(double abc[3], double sol1, double sol2);
#endif
