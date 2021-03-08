/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:06:21 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/08 15:44:23 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math_utils.h"

/*
**	Check if the text given is a valid representation of a number
**	before validating its value like an atoi.
*/

int		validate_int(char *str, int min, int max)
{
	int i;
	int out;

	i = 0;
	if (str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		config_err("Value is not an integer.\n");
	out = ft_atoi(str);
	if (out < min || out > max)
		config_err("Integer out of range.\n");
	return (out);
}

/*
**	Check if the text given is a valid representation of a floating
**	point number before validating its value.
*/

double	validate_double(char *str, long double min, long double max)
{
	int		i;
	double	out;

	i = 0;
	if (str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		config_err("Float has extraneus characters.\n");
	out = ft_atof(str);
	if (out < min || out > max)
		config_err("Double out of range.\n");
	return (ft_atof(str));
}

/*
**	Check if the text is a set of three integers, separated only by commas,
**	in the range of 0-255 (unisgned char).
**	The colour is stored in an integer using said values.
*/

void	validate_colour(char *text, t_colour out)
{
	char		**colours;
	int			i;

	if (!(colours = ft_split(text, ',')))
		config_err("Failed split.\n");
	i = 0;
	while (i < 3 && colours[i])
	{
		out[i] = validate_int(colours[i], 0, 256);
		free(colours[i++]);
	}
	if (i < 3)
		config_err("Too few components for colour.\n");
	if (colours[i])
		config_err("Too many components for colour.\n");
	free(colours);
}

t_coord	validate_coordinates(char *text)
{
	char	**coords;
	int		i;
	t_coord	out;

	if (!(coords = ft_split(text, ',')))
		config_err("Failed split.\n");
	i = 0;
	while (i < 3)
	{
		if (!coords[i])
			config_err("Too few components for vector/coord.\n");
		out.x[i] = validate_double(coords[i], -HUGE_VAL, HUGE_VAL);
		free(coords[i++]);
	}
	if (coords[i])
		config_err("Too many components for vector/coord.\n");
	free(coords);
	return (out);
}

int		param_num(char **param)
{
	int		i;

	i = 0;
	while (param[i])
		i++;
	return (i);
}
