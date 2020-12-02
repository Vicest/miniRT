/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:29:19 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/02 14:02:45 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"
#include <stdlib.h>

static void	fill_camera(t_camera *pcam, char** params)
{
	if (!pcam || !params || !(*params))
		return ; //TODO Bad usage
	pcam->next = NULL;
	/*
	pcam->pos = params[1];
	pcam->dir = params[2];
	pcam->fov = params[3];
	*/
}

void		add_camera(t_camera **c_lst, char **params)
{
	t_camera *new;

	if (c_lst == NULL)
		return ; //TODO Error null camera_list
	if (!(new = malloc(sizeof(t_camera))))
		return ; //TODO Sys Error
	//TODO Fill new
	if (*c_lst == NULL)
		*c_lst = new;
	else {
		while ((*c_lst)->next != NULL)
			*c_lst = (*c_lst)->next;
		(*c_lst)->next = new;
	}
}

