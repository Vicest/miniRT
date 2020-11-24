/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:00:09 by vicmarti          #+#    #+#             */
/*   Updated: 2020/11/24 12:33:32 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int		main(char **args, int argn)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window();
	mlx_loop(mlx_ptr);
}
