/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 13:09:59 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/07 19:04:04 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATIONS_H
# define VALIDATIONS_H
# include "minirt.h"

int				param_num(char **param);
int				validate_int(char *text, int min, int max);
void			validate_colour(char *text, t_colour out);
double			validate_double(char *str, long double min, long double max);
t_coord			validate_coordinates(char *text);
#endif
