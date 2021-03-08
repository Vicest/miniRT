/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmpstore.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 14:31:25 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/08 13:06:03 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "minirt.h"

static void	put_header(int fd, int size, int bpp, int dim[2])
{
	char	head_buff[54];

	ft_memcpy(head_buff, "BM", 2);
	size += 54;
	ft_memcpy(head_buff + 2, &size, 4);
	size -= 54;
	ft_memcpy(head_buff + 6, "\f\n\017\017\x36\0\0\0", 8);
	ft_memcpy(head_buff + 14, "\x28\0\0\0", 4);
	ft_memcpy(head_buff + 18, &dim[0], 4);
	ft_memcpy(head_buff + 22, &dim[1], 4);
	ft_memcpy(head_buff + 26, "\x01\0", 2);
	ft_memcpy(head_buff + 28, &bpp, 2);
	ft_memcpy(head_buff + 30, "\0\0\0\0", 4);
	ft_memcpy(head_buff + 34, &size, 4);
	ft_memcpy(head_buff + 38, "\x13\x0B\0\0\x13\x0B\0\0\0\0\0\0\0\0\0\0", 16);
	write(fd, head_buff, 54);

}

int			save_bmp(t_img img, char *name, int dim[2])
{
	int		padding;
	int		row_size;
	int		fd;

	if (NULL == (name = ft_strjoin(name, ".bmp")))
		config_err("Bad strjoin output.\n");
	if ((fd = open(name, O_CREAT | O_RDWR, 0644)) < 0)
		config_err("Could not create file.\n");
	free(name);
	row_size = (img.bpp * dim[0] / 8);
	padding =  4 - (row_size % 4);
	if (padding == 4)
		padding = 0;
	put_header(fd, (padding + row_size) * dim[1], img.bpp, dim);
	while (dim[1]-- > 0)
	{
		write(fd, img.addr + dim[1] * row_size, row_size);
		write(fd, "\0\0\0\0", padding);
	}
	close(fd);
	return (0);
}
