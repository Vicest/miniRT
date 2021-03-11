/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:49:57 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/11 13:12:49 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "figures.h"

int			inside_check(t_coord p, t_coord nv, t_coord *vertix, int v_num)
{
	t_coord		side;
	t_coord		v_to_p;
	int			sign_cnt;
	int			i;

	sign_cnt = 0;
	i = -1;
	while (++i < v_num)
	{
		vect_sub(&v_to_p, p, vertix[i]);
		vect_sub(&side, vertix[(i + 1) % v_num], vertix[i]);
		cross_prod(&side, side, v_to_p);
		if (signbit(dot_prod(side, nv)) == 1)
			sign_cnt++;
		if (sign_cnt != 0 && sign_cnt - 1 != i)
			return (0);
	}
	return (sign_cnt == 0 || sign_cnt == v_num);
}
