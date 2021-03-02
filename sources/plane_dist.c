/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_dist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:52:16 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/02 15:52:44 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "figures.h"

long double	plane_dist(t_coord orig, t_coord dir, long double iterm, t_coord n)
{
	long double	d;

	d = iterm - dot_prod(orig, n);
	d /= dot_prod(dir, n);
	if (isnan(d) || signbit(d) == 1 || equals_zero(d))
		d = NAN;
}
