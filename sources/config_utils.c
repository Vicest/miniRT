/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:48:56 by vicmarti          #+#    #+#             */
/*   Updated: 2020/11/25 14:09:20 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**	Check if the text given is a valid representation of a number
**	before validating its value like an atoi.
*/

int		validate_int(char *text, int min_val, int max_val)
{
	int out;

	out = ft_atoi(text);
	if (ft_numdgts(out) != ft_strlen(text))
		return (-1);	//TODO: Error text is not only a number
	if (out <= min_val || out >= max_val)
		return (-1);	//TODO: Error int is out of range
	return (out);
}

/*
**	Check if the text given is a valid representation of a floating
**	point number before validating its value.
*/

double	validate_dbl(char *text, double min_val, double max_val)
{/*
	int out;

	out = ft_atoi(text);
	if (ft_numdgts(out) != ft_strlen(text))
		return (-1);	//TODO: Error text is not only a number
	if (out <= min_val || out >= max_val)
		return (-1);	//TODO: Error int is out of range
	return (out);*/
}
int		validate_colour(char *text)
{
	int out;

	out = ft_atoi(text);
	if (ft_numdgts(out) != ft_strlen(text))
		return (-1);	//TODO: Error text is not only a number
	if (out <= min_val || out >= max_val)
		return (-1);	//TODO: Error int is out of range
	return (out);
}

/*
**	Resolution, can only be set once, and must be exactly two values.
*/

void	store_resolution(t_scene scn, char **element)
{
	if (scn->flags & FLAG_RES)
		return ;//TODO Error handling, resolution already assigned
	scn->res[0] = validate_int(element[1], 1, MAX_XRES);
	scn->res[1] = validate_int(element[2], 1, MAX_YRES);
	scn->flags =| FLAG_RES;
	if (element[3] != NULL)
		return ; //TODO: Error handling, too many values for resolution.
}

/*
**	Ambient, can only be set once, and must be exactly a double and a colour.
*/

void	store_ambient(t_scene scn, char **element)
{
	int i;

	if (scn->flags & FLAG_AMB)
		return ;//TODO Error handling, ambient light already assigned.
	scn->amb->ratio = validate_double(element[1], 0.0, 1.0);
	i = 0;
	while (i < 3)
	{
		scn->amb->col[i] = validate_int(element[i + 2], 0, 255);
		i++;
	}
	scn->flags =| FLAG_AMB;
	if (element[i + 2] != NULL)
		return ; //TODO: Error handling, too many values for resolution.
}
