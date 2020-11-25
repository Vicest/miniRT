/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:32:16 by vicmarti          #+#    #+#             */
/*   Updated: 2020/10/04 13:25:41 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(long long n, int fd)
{
	unsigned long long n_pos;

	n_pos = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n_pos = -1 * n;
	}
	if (n_pos / 10)
		ft_putnbr_fd(n_pos / 10, fd);
	ft_putchar_fd((n_pos % 10) + '0', fd);
}
