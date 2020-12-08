/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:00:09 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/08 14:28:50 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx/mlx.h"
#include <stdlib.h>

int			main(int argn, char **args)
{
	t_scene	scn;
	void	*mlx_ptr;
	void	*win_ptr;

	if (argn != 2)
		return (1); //TODO: Error handling.
	save_conf(args[1], &scn);

	mlx_ptr = mlx_init();//TODO: Error hanlding plz
	win_ptr = mlx_new_window(mlx_ptr, scn.res[0], scn.res[1], "miniRT"); //TODO: Moar error
	mlx_loop(mlx_ptr);
	mlx_destroy_window(mlx_ptr, win_ptr);
	//mlx_destroy_display(mlx_ptr);
	//TODO: Bad place, needs new function.
	printf("YO");
	pop_all_c(&(scn.cam));
	pop_all_l(&(scn.lgt));
	printf("LO");
	system("leaks -quiet miniRT");
	return (0);
}
