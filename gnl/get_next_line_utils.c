/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 23:07:52 by vicmarti          #+#    #+#             */
/*   Updated: 2020/02/09 21:12:19 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_fileinfo	*ft_add(int fd, t_fileinfo **list)
{
	t_fileinfo	*new;

	if (!list || !(new = malloc(sizeof(t_fileinfo))))
		return (NULL);
	new->next = *list;
	*list = new;
	new->fd = fd;
	new->curr = BUFFER_SIZE;
	return (new);
}

t_fileinfo	*ft_find(int fd, t_fileinfo *list)
{
	while (list)
	{
		if (list->fd == fd)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void		ft_rmv(t_fileinfo **list, t_fileinfo **garbage)
{
	t_fileinfo	*prev;

	if (!list || !*list)
		return ;
	if (*list == *garbage)
	{
		*list = (*list)->next;
		free(*garbage);
		*garbage = NULL;
		return ;
	}
	prev = *list;
	while (prev->next != *garbage)
		prev = prev->next;
	if (prev->next)
	{
		prev->next = (*garbage)->next;
		free(*garbage);
	}
}
