/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 13:09:59 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/11 14:36:15 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATIONS_H
# define VALIDATIONS_H
# include "minirt.h"

//typedef unsigned int	t_colour;

int				validate_int(char *text, int min_val, int max_val);
t_colour		validate_colour(char *text);
double			validate_double(char *str);
t_coord			validate_coordinates(char *text);
t_vector		validate_vector(char *text);
#endif
