/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:29:19 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/28 20:56:13 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"
#include "minirt.h"
#include <stdlib.h>

static void	pop_camera(t_camera **c_lst)
{
	t_camera	*aux;

	if (c_lst && (*c_lst))
	{
		aux = (*c_lst)->next;
		free(*c_lst);
		(*c_lst) = aux;
	}
}

/*
**	Free the memory of all elements of the list starting at the given node.
**	Free the reference to the first one as well.
*/

void		pop_all_c(t_camera **c_lst)
{
	if (c_lst)
	{
		while ((*c_lst))
			pop_camera(c_lst);
	}
}

/*
**	Adds a new element to the list at the start.
*/

void		push_camera(t_camera **c_lst)
{
	t_camera *new;

	if (c_lst == NULL)
		config_err("Camera list destination is NULL\n");
	if (!(new = malloc(sizeof(t_camera))))
		config_err("Could not allocate mem.\n");
	if (*c_lst == NULL)
	{
		new->next = new;
		new->prev = new;
	}
	else
	{
		new->next = *c_lst;
		new->prev = (*c_lst)->prev;
		new->next->prev = new;
		new->prev->next = new;
	}
	*c_lst = new;
}
