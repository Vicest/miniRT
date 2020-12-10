/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 13:09:59 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/10 14:14:00 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATIONS_H
# define VALIDATIONS_H
# include "minirt.h"

//typedef unsigned int	t_colour;

int				validate_int(char *text, int min_val, int max_val);
t_colour		validate_colour(char *text);
double			validate_double(char *str);
void			validate_coordinates(t_coord *out, char *text);
void			validate_vector(t_coord *out, char *text);
#endif