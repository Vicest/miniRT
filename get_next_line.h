/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:41:26 by vicmarti          #+#    #+#             */
/*   Updated: 2020/02/09 21:12:22 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

typedef	struct	s_fileinfo
{
	int					fd;
	unsigned int		curr;
	unsigned char		pending[BUFFER_SIZE + 1];
	struct s_fileinfo	*next;
}				t_fileinfo;

int				get_next_line(int fd, char **line);

t_fileinfo		*ft_add(int fd, t_fileinfo **list);
t_fileinfo		*ft_find(int fd, t_fileinfo *list);
void			ft_rmv(t_fileinfo **list, t_fileinfo **garbage);
#endif
