/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:11:50 by vicmarti          #+#    #+#             */
/*   Updated: 2021/03/07 16:57:32 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt.h"

void		pitch(t_coord *rot, t_coord v, long double angle)
{
	t_coord	rot_buff;

	ft_memcpy(&rot_buff, &v, sizeof(t_coord));
	rot->x[0] = cosl(angle) * rot_buff.x[0] - sinl(angle) * rot_buff.x[2];
	rot->x[1] = rot_buff.x[1];
	rot->x[2] = cosl(angle) * rot_buff.x[2] + sinl(angle) * rot_buff.x[0];
}

void		yaw(t_coord *rot, t_coord v, long double angle)
{
	t_coord	rot_buff;

	ft_memcpy(&rot_buff, &v, sizeof(t_coord));
	rot->x[0] = cosl(angle) * rot_buff.x[0] - sinl(angle) * rot_buff.x[1];
	rot->x[1] = cosl(angle) * rot_buff.x[1] + sinl(angle) * rot_buff.x[0];
	rot->x[2] = rot_buff.x[2];
}

void		roll(t_coord *rot, t_coord v, long double angle)
{
	t_coord	rot_buff;

	ft_memcpy(&rot_buff, &v, sizeof(t_coord));
	rot->x[0] = rot_buff.x[0];
	rot->x[1] = cosl(angle) * rot_buff.x[1] - sinl(angle) * rot_buff.x[2];
	rot->x[2] = cosl(angle) * rot_buff.x[2] + sinl(angle) * v.x[1];
}
