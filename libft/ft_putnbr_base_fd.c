/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:32:16 by vicmarti          #+#    #+#             */
/*   Updated: 2020/11/03 10:18:17 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_fd(long long n, char *base, size_t baselen, int fd)
{
	unsigned long long n_pos;

	n_pos = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n_pos = -1 * n;
	}
	if (n_pos / baselen)
		ft_putnbr_base_fd(n_pos / baselen, base, baselen, fd);
	ft_putchar_fd(base[(n_pos % baselen)], fd);
}
