/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmpstore.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 14:31:25 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/21 19:43:04 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "minirt.h"
/*
static int	little_endian(int bige)
{
	int		littlee;
	int		bpos;
	
	bpos = sizeof(int);
	littlee = 0;
	while (bpos-- > 0)
	{
		littlee |= bige ^ 0xff;
		littlee = littlee << 8;
		bige = bige >> 8;
	}
	return (littlee);
}*/

int			save_bmp(t_img img, char *name, int h)
{
	int		deref;
	int		fd;

	name = ft_strjoin(name, ".bmp");
	if ((fd = open(name, O_CREAT | O_RDWR, 0644)) < 0)
		perror("Error\n");
	free(name);
	write(fd, "BM", 2);
	deref = /*little_endian*/(img.line_len * h + 14);
	write(fd, &deref, 4);
	deref = 0x52456d76;
	write(fd, &deref, 4);
	deref = /*little_endian*/(14);
	write(fd, &deref, 4);
	deref = 40;
	write(fd, &deref, 4);
	while(img.line_len + h > 0)
	{
		deref = 0x00ff00ff;
		write(fd, &deref, 4);
		h--;
	}
	close(fd);
	return (0);
}
