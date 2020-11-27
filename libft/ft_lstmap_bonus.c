/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 11:31:34 by vicmarti          #+#    #+#             */
/*   Updated: 2020/01/22 11:27:38 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mapped;

	(void)del;
	mapped = NULL;
	while (lst)
	{
		ft_lstadd_back(&mapped, ft_lstnew(f(lst->content)));
		lst = lst->next;
	}
	return (mapped);
}
