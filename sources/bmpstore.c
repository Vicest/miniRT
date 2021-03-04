/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmpstore.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 14:31:25 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/04 14:50:17 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "minirt.h"

int			save_bmp(t_img img, char *name, int dim[2])
{
	char	head_buff[54];
	int		aux;
	int		size;
	int		fd;

	name = ft_strjoin(name, ".bmp");
	if ((fd = open(name, O_CREAT | O_RDWR, 0644)) < 0)
		perror("Error\n");
	free(name);
	size = (img.bpp * dim[0] / 32) * 4 * dim[1];
	ft_memcpy(head_buff, "BM", 2);
	aux = size + 54;
	ft_memcpy(head_buff + 2, &aux, 4);
	ft_memcpy(head_buff + 6, "\f\n\017\017\x36\0\0\0", 8);
	ft_memcpy(head_buff + 14, "\x28\0\0\0", 4);
	ft_memcpy(head_buff + 18, &dim[0], 4);
	ft_memcpy(head_buff + 22, &dim[1], 4);
	ft_memcpy(head_buff + 26, "\x01\0", 2);
	ft_memcpy(head_buff + 28, &img.bpp, 2);
	ft_memcpy(head_buff + 30, "\0\0\0\0", 4);
	ft_memcpy(head_buff + 34, &size, 4);
	ft_memcpy(head_buff + 38, "\x13\x0B\0\0\x13\x0B\0\0\0\0\0\0\0\0\0\0", 16);
	write(fd, head_buff, 54);
	write(fd, img.addr, size);
	close(fd);
	return (0);
}
