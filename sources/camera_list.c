/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:29:19 by vicmarti          #+#    #+#             */
/*   Updated: 2021/01/08 13:02:13 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"
#include <stdlib.h>

/*
**	Cameras are stored in a sort of simplified doubly-linked list.
*/

/*
static void	fill_camera(t_camera *pcam, char** params)
{
	if (!pcam || !params || !(*params))
		return ; //TODO Bad usage
	pcam->next = NULL;
}*/

/*
**	Clear the first element of the list, much like a pop in a stack.
*/

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
		exit(-1);//config_err("Camera list destination is NULL\n");
	if (!(new = malloc(sizeof(t_camera))))
		exit(-1);//config_err(NULL);
	if (*c_lst == NULL)
	{
		new->next = new;
		new->prev = new;
	} else
	{
		new->next = *c_lst;
		new->prev = (*c_lst)->prev;
		new->next->prev = new;
		new->prev->next = new;
	}
	*c_lst = new;
}
