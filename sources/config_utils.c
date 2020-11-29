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
	if (out >= min_val || out <= max_val)
		return (-1);	//TODO: Error int is out of range
	return (out);
}

void	store_resolution(t_scene scn, char **element)
{
	int aux;

	if (scn->res[0] != 0 && scn->res[1] != 0)
		return ;//TODO Error handling, resolution already assigned
	scn->res[0] = validate_int(element[1], MIN_XRES, MAX_XRES);
	scn->res[1] = validate_int(element[2], MIN_YRES, MAX_YRES);
	if (element[3] != NULL)
		return ; //TODO: Error handling, too many values for resolution.
}
