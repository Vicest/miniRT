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

void	validate_uint(char *text, unsigned min_val,  unsigned max_val)
{
	unsigned	out;

	out = ft_atoi(text);
	if (ft_numdgts(out) != ft_strlen(text))
		return (-1);	//TODO: Error handling
	if (out >= min_val || out <= max_val)
		return (-1);	//TODO: Error handling
	return (out);
}


void	store_resolution(t_scene scn, char **element)
{
	int aux;

	if (scn->res[0] != 0 && scn->res[1] != 0)
		return ;//TODO Error handling

	aux = ft_atoi(element[1])
	

