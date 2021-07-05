/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:37:30 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/05 17:38:46 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	set_vertical_ray(t_data *data, t_ray *r)
{
	if (r->a > M_PI / 2 && r->a < M_PI + M_PI / 2)
	{
		r->x = (((int)data->player->x >> 6) << 6) - 0.0001;
		r->y = (data->player->x - r->x) * -tan(r->a) + data->player->y;
		r->xo = -64;
		r->yo = -r->xo * -tan(r->a);
	}
	if (r->a < M_PI / 2 || r->a > M_PI + M_PI / 2)
	{
		r->x = (((int)data->player->x >> 6) << 6) + 64;
		r->y = (data->player->x - r->x) * -tan(r->a) + data->player->y;
		r->xo = 64;
		r->yo = -r->xo * -tan(r->a);
	}
	if (r->a == M_PI / 2 || r->a == M_PI + M_PI / 2 )
		return (-1);
}

int	set_horizontal_ray(t_data *data, t_ray *r)
{
	if (r->a > M_PI)
	{
		r->y = (((int)data->player->y >> 6) << 6) - 0.0001;
		r->x = (data->player->y - r->y) * (-1 / tan(r->a)) + data->player->x;
		r->yo = -64;
		r->xo = -r->yo * (-1 / tan(r->a));
	}
	if (r->a < M_PI)
	{
		r->y = (((int)data->player->y >> 6) << 6) + 64;
		r->x = (data->player->y - r->y) * (-1 / tan(r->a)) + data->player->x;
		r->yo = 64;
		r->xo = -r->yo * (-1 / tan(r->a));
	}
	if (r->a == 0 || r->a == M_PI)
		return (-1);
}

void	search_vert_walls(t_data *data, t_ray *r, t_pos *m)
{
	while (m->y >= 0 && m->y < data->map->map_y && m->x >= 0 && m->x < data
		->map->map_x)
	{
		m->x = (int)(r->x) >> 6;
		m->y = (int)(r->y) >> 6;
		m->z = m->y * data->map->map_x + m->x;
		if (m->x >= data->map->map_x || m->y >= data->map->map_y || m->x < 0
			|| m->y < 0)
			break ;
		if (m->z > 0 && m->z < data->map->map_x * data->map->map_y && data
			->map->map[m->y][m->x] == 2)
			is_sprite(data, r, m);
		if (m->z > 0 && m->z < data->map->map_x * data->map->map_y && data
			->map->map[m->y][m->x] == 1)
			break ;
		else
		{
			r->x += r->xo;
			r->y += r->yo;
		}
	}
}

void	search_hor_wall(t_data *data, t_ray *r, t_pos *m)
{
	while (m->y >= 0 && m->y < data->map->map_y && m->x >= 0 && m->x < data->map
		->map_x)
	{
		m->x = (int)(r->x) >> 6;
		m->y = (int)(r->y) >> 6;
		m->z = m->y * data->map->map_x + m->x;
		if (m->x >= data->map->map_x || m->y >= data->map->map_y || m->x < 0
			|| m->y < 0)
			break ;
		if (m->z > 0 && m->z < data->map->map_x * data->map->map_y && data->map
			->map[m->y][m->x] == 2)
			is_sprite(data, r, m);
		if (m->z > 0 && m->z < data->map->map_x * data->map->map_y && data->map
			->map[m->y][m->x] == 1)
			break ;
		else
		{
			r->x += r->xo;
			r->y += r->yo;
		}
	}
}
