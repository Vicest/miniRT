/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:17:00 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/08 15:55:36 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOURS_H
# define COLOURS_H
# include "../libft/libft.h"

typedef unsigned char	t_colour[3];

unsigned	col2uint(t_colour c);
void		mix_colour(t_colour c1, t_colour c2);
void		intensity(t_colour c, long double i_factor);
void		filter_colour(t_colour final, t_colour c1, t_colour c2);
#endif
