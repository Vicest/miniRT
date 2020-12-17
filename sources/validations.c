/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:06:21 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/13 12:32:22 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math_utils.h"

/*
**	Check if the text given is a valid representation of a number
**	before validating its value like an atoi.
*/

int				validate_int(char *text, int min_val, int max_val)
{
	int out;

	out = ft_atoi(text);
	if (ft_numdgts(out) != ft_strlen(text))
		exit(-1);	//TODO: Error text is not only a number
	if (out < min_val || out > max_val)
		exit(-1);	//TODO: Error int is out of range
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
		exit(-1); //TODO: Error handling
	return ft_atof(str);
}

/*
**	Check if the text is a set of three integers, separated only by commas,
**	in the range of 0-255 (unisgned char).
**	The colour is stored in an integer using said values.
*/

t_colour		validate_colour(char *text)
{
	char		**colours;
	t_colour	out;
	int			i;
	int			colour_comp;

	if (!(colours = ft_split(text, ',')))
		exit(-1); //TODO: Syserror
	i = 0;
	out = 0;
	while (i < 3 && *(colours[i]))
	{
		colour_comp = validate_int(colours[i], 0, 255);
		free(colours[i++]);
		out = out << 8;
		out += colour_comp;
	}
	if (i > 3 || colours[i])
		exit (-1); //TODO: Can only have 3 colours.
	free(colours);
	return (out);
}

t_coord			validate_coordinates(char *text)
{
	char	**coords;
	int		i;
	t_coord	out;

	if (!(coords = ft_split(text, ',')))
		exit(-1); //TODO: Syserror
	i = 0;
	if (!coords[0] || !coords[1] || !coords[2])
		exit (-1); //TODO: Must have 3 components.
	out.x = validate_double(coords[0]);
	out.y = validate_double(coords[1]);
	out.z = validate_double(coords[2]);
	while (i < 3)
		free(coords[i++]);
	if (i > 3 || coords[i])
		exit (-1); //TODO: Can only have 3 coords.
	free(coords);
	return (out);
}

t_vector		validate_vector(char *text)
{
	char	**points;
	int		i;
	t_vector out;

	if (!(points = ft_split(text, ',')))
		exit(-1); //TODO: Syserror
	i = 0;
	if (!points[0] || !points[1] || !points[2])
		exit (-1); //TODO: Must have 3 components.
	out.x = validate_double(points[0]);
	out.y = validate_double(points[1]);
	out.z = validate_double(points[2]);
	while (i < 3)
		free(points[i++]);
	if (!is_normal(out))
		exit (-1); //TODO: Not normalized
	if (i > 3 || points[i])
		exit (-1); //TODO: Can only have 3 components.
	free(points);
	return (out);
}
