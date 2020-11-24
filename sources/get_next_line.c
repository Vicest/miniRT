/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:47:44 by vicmarti          #+#    #+#             */
/*   Updated: 2020/02/14 00:18:06 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Refresh the read buffer and its status.
** Cleans buffer status if EOF is reached.
** Propagates errors.
*/

static int	ft_read(t_fileinfo **list, t_fileinfo **fi)
{
	int				rout;

	if (1 > (rout = read((*fi)->fd, (*fi)->pending, BUFFER_SIZE)))
	{
		ft_rmv(list, fi);
		return (rout);
	}
	(*fi)->pending[rout] = 0;
	(*fi)->curr = 0;
	return (1);
}

/*
** Make sure BUFFER_SIZE > 0, fd >= 0, *ln is the empty str.
** Create a struct to manage data if it is non-existing.
** Defines fi as the struct associated to the fd gnl reads from.
** Propagates errors.
*/

static int	ft_initialize(t_fileinfo **lst, t_fileinfo **fi, int fd, char **ln)
{
	if (fd < 0 || !ln || BUFFER_SIZE < 1)
		return (-1);
	if (!(*ln = malloc(1)))
		return (-1);
	**ln = 0;
	if ((*fi = ft_find(fd, *lst)))
		return (1);
	if ((*fi = ft_add(fd, lst)))
		return (ft_read(lst, fi));
	return (-1);
}

/*
** Concatenate the buffer until empty or NL is reached.
** Propagates errors.
*/

static int	ft_fill(char **str, size_t *len, t_fileinfo *fi)
{
	unsigned int	i;
	unsigned int	clen;
	char			*aux;

	clen = 0;
	while (fi->pending[fi->curr + clen] != 0 &&
			fi->pending[fi->curr + clen] != '\n')
		clen++;
	aux = *str;
	if (!(*str = malloc(sizeof(char) * (*len + clen + 1))))
		return (0);
	(*str)[*len + clen] = 0;
	i = -1;
	while (++i < *len)
		(*str)[i] = aux[i];
	free(aux);
	*len += clen;
	while (fi->pending[fi->curr] != 0 && fi->pending[fi->curr] != '\n')
		(*str)[i++] = fi->pending[fi->curr++];
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static t_fileinfo	*lst;
	t_fileinfo			*fi;
	int					out;
	size_t				len;

	if (1 != (out = ft_initialize(&lst, &fi, fd, line)))
		return (out);
	len = 0;
	while (fi->pending[fi->curr] != '\n')
	{
		if (fi->pending[fi->curr] == 0 && 1 != (out = ft_read(&lst, &fi)))
			return (out);
		if (!ft_fill(line, &len, fi))
			return (-1);
	}
	fi->curr++;
	return (1);
}
