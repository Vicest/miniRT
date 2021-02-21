/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:11:21 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/21 18:35:47 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minirt.h"

void	config_err(char *err_str)
{
	write(1, "Error\n", 6);
	write(1, err_str, ft_strlen(err_str));
	exit(-1);
}
