/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:06:21 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/03 14:38:05 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math_utils.h"

/*
**	Check if the text given is a valid representation of a number
**	before validating its value like an atoi.
*/

int				validate_int(char *str, int min_val, int max_val)
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
	if (out < min_val || out > max_val)
		config_err("Integer out of range.\n");
	return (out);
}

/*
**	Check if the text given is a valid representation of a floating
**	point number before validating its value.
**	/TODO: Dolor de muelas. Únicamente verifica que la cadena va bien.
*/

double			validate_double(char *str)
{
	int i;
	
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
	return (ft_atof(str));
}

/*
**	Check if the text is a set of three integers, separated only by commas,
**	in the range of 0-255 (unisgned char).
**	The colour is stored in an integer using said values.
*/

void		validate_colour(char *text, t_colour out)
{
	char		**colours;
	int			i;

	if (!(colours = ft_split(text, ',')))
		exit(-1); //TODO: Syserror
	i = 0;
	while (i < 3 && colours[i])
	{
		out[i] = validate_int(colours[i], 0, 255);
		free(colours[i++]);
	}
	if (i < 3)
		config_err("Too few components for colour.\n");
	if (colours[i])
		config_err("Too many components for colour.\n");
	free(colours);
}

t_coord			validate_coordinates(char *text)
{
	char	**coords;
	int		i;
	t_coord	out;

	if (!(coords = ft_split(text, ',')))
		exit(-1); //TODO: Syserror
	i = 0;
	while (i < 3)
	{
		if (!coords[i])
			config_err("Too few components for vector/coord.\n");
		out.x[i] = validate_double(coords[i]);
		free(coords[i++]);
	}
	if (coords[i])
		config_err("Too many components for vector/coord.\n");
	free(coords);
	return (out);
}


//TODO: I have doubts, this looks like different work somewhere else.
t_coord		validate_direction(char *text)
{
	t_vector out;

	out.dir = validate_coordinates(text);
	if (!equals_zero(fabsl(norm(out) - 1.0L)))
		config_err("Camera direction is not normalized.\n");
	printf("Norm is:%Lf\n", norm(out));
	return (out.dir);
}
