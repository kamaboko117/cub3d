/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawutils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:17:56 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/06 17:55:12 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	set_tx(t_data *data, t_ray *r)
{
	int	tx;

	if (r->txt == data->so_texture || r->txt == data->no_texture)
	{
		tx = ((int)(r->x) *(r->txt->height / data->map->map_s)) % r->txt
			->height;
		if (r->a < M_PI)
			tx = r->txt->height - 1 - tx;
	}
	else
	{
		tx = ((int)(r->y) *(r->txt->height / data->map->map_s)) % r->txt
			->height;
		if (r->a > M_PI / 2 && r->a < M_PI + (M_PI / 2))
			tx = r->txt->height - 1 - tx;
	}
	return (tx);
}

void	imgdrawtexturecol(t_pos a, t_pos b, t_data *data, t_ray *r)
{
	int		i;
	char	*src;
	float	ty;
	float	tx;

	i = a.y;
	ty = r->toffset * r->step;
	tx = set_tx(data, r);
	while (i < b.y)
	{
		src = r->txt->addr + (int)ty * r->txt->line_len + (int)tx * (r->txt
				->bpp / 8);
		*(unsigned int *)(data->img->addr + (i * data->img->line_len + a.x
					* (data->img->bpp / 8))) = *(unsigned int*)src;
		ty += r->step;
		i++;
	}
}

void	draw_walls(t_data *data, t_raydist rdist, int r, t_ray *ray)
{
	t_pos	a;
	t_pos	b;
	float	lineH;
	float	lineO;

	lineH = (data->map->map_s * data->win_h) / rdist.td[r];
	ray->step = ray->txt->height / lineH;
	ray->toffset = 0;
	if (lineH > data->win_h)
	{
		ray->toffset = (lineH - data->win_h) / 2;
		lineH = data->win_h;
	}
	lineO = data->win_h / 2 - lineH / 2;
	a.x = 1 * r;
	b.x = 1 * r;
	a.y = lineO;
	b.y = lineH + lineO;
	imgdrawtexturecol(a, b, data, ray);
}

void	imgdrawray(t_data *data, t_ray *r, int color)
{
	t_pos	a;
	t_pos	b;

	a.x = (int)data->player->x;
	a.y = (int)data->player->y;
	b.x = (int)r->x;
	b.y = (int)r->y;
	a.color = color;
	imgdrawline(a, b, data);
}
