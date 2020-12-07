/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:29:19 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/07 13:08:26 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"
#include <stdlib.h>

/*
**	Aux function to initialize de values of a camera.
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

void		pop_camera(t_camera **c_lst)
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

void		pop_all(t_camera **c_lst)
{
	if (c_lst)
	{
		while ((*c_lst))
			pop_camera(c_lst);
	}
}

/*
**	Adds a new element to the list at the start. Behaves like a stack.
*/

void		push_camera(t_camera **c_lst)
{
	t_camera *new;

	if (c_lst == NULL)
		return ; //TODO Error null camera_list
	if (!(new = malloc(sizeof(t_camera))))
		return ; //TODO Sys Error
	new->next = *c_lst;
	(*c_lst) = new;
}

/*
** /TODO: Iterate: Apply a function to every element of the list.
*/
