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

void	add_resolution(t_scene scn, char **element)
{
	int aux;

	if (scn->res[0] != 0 && scn->res[1] != 0)
		return ;//TODO Error handling

	aux = ft_atoi(element[1])
	

