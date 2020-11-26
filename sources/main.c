/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:00:09 by vicmarti          #+#    #+#             */
/*   Updated: 2020/11/26 09:48:29 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minlibx/mlx.h"

int		main(int argn, char **args)
{
	t_scene	scn;
	void	*mlx_ptr;
	void	*win_ptr;

	if (argn != 1)
		return (1); //TODO: Error handling.
	save_conf(args[1], scn);

	mlx_ptr = mlx_init();//TODO: Error hanlding plz
	win_ptr = mlx_new_window(mlx_ptr, 1000, 600, "Ah-ha!");
	mlx_loop(mlx_ptr);
	return (0);
}
