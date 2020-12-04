/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:48:56 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/04 14:02:17 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	return ft_atoi(str);
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
	free(colours);
	if (i > 3 || colours[i])
		exit (-1); //TODO: Can only have 3 colours.
	return (out);
}

/*
**	Resolution, can only be set once, and must be exactly two values.
*/

void	store_resolution(t_scene *pscn, char **element)
{
	if (pscn->flags & FLAG_RES)
		return ;//TODO Error handling, resolution already assigned
	pscn->res[0] = validate_int(element[1], 1, MAX_XRES);
	pscn->res[1] = validate_int(element[2], 1, MAX_YRES);
	pscn->flags |= FLAG_RES;
	if (element[3] != NULL)
	{
		write(1,element[3], 2);
		printf("STRERR: %s\n", strerror(5));
		exit(-1);//TODO: Error handling, too many values for resolution.
	}
}

/*
**	Ambient, can only be set once, and must be exactly a double and a colour.
*/

void	store_ambient(t_scene *pscn, char **element)
{
	if (pscn->flags & FLAG_AMB)
		return ;//TODO Error handling, ambient light already assigned.
	pscn->amb.ratio = validate_double(element[1]);//, 0.0, 1.0);
	pscn->amb.col = validate_colour(element[2]);
	pscn->flags |= FLAG_AMB;
	if (element[3] != NULL)
		return ; //TODO: Error handling, too many values for resolution.
}

void	store_camera(t_scene *pscn, char **params)
{
	//TODO: Do proper parameter validation.
	push_camera(&(pscn->cam), params);
}
