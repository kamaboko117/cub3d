/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:26:42 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/09 19:24:23 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

float	calculate_angle(t_data *data, int x, int y)
{
	float	hypotenuse;
	float	angle;
	t_pos	*origin;
	float	cos;

	origin = posstructinit();
	x -= data->player->x;
	y -= data->player->y;
	hypotenuse = dist(origin, x, y);
	cos = (x) / hypotenuse;
	if (y < 0)
		angle = -acos(cos);
	if (y >= 0)
		angle = acos(cos);
	angle = angle - data->player->a;
	if (angle <= M_PI + M_PI / 3)
		angle += 2 * M_PI;
	if (angle >= M_PI + M_PI / 3)
		angle -= 2 * M_PI;
	free(origin);
	return (angle);
}

double	limit_angle(double a)
{
	if (a < 0)
		a += 2 * M_PI;
	if (a > 2 * M_PI)
		a -= 2 * M_PI;
	return (a);
}

t_pos	*tpos_set(int x, int y, int z, int color)
{
	t_pos	*p;

	p = posstructinit();
	if (p == NULL)
		return (NULL);
	p->x = x;
	p->y = y;
	p->z = z;
	p->color = color;
	return (p);
}
