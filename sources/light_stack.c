/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 10:21:09 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/08 10:28:54 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lists.h"
#include <stdlib.h>

/*
**	Clear the first element of the list, much like a pop in a stack.
*/

void		pop_light(t_light **l_lst)
{
	t_light	*aux;

	if (l_lst && (*l_lst))
	{
		aux = (*l_lst)->next;
		free(*l_lst);
		(*l_lst) = aux;
	}
}

/*
**	Free the memory of all elements of the list starting at the given node.
**	Free the reference to the first one as well.
*/

void		pop_all_l(t_light **l_lst)
{
	if (l_lst)
	{
		while ((*l_lst))
			pop_light(l_lst);
	}
}

/*
**	Adds a new element to the list at the start. Behaves like a stack.
*/

void		push_light(t_light **l_lst)
{
	t_light *new;

	if (l_lst == NULL)
		return ; //TODO Error null light_list
	if (!(new = malloc(sizeof(t_light))))
		return ; //TODO Sys Error
	new->next = *l_lst;
	(*l_lst) = new;
}
