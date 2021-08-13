/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:17:39 by asaboure          #+#    #+#             */
/*   Updated: 2021/08/13 16:52:35 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_map	*mapstructinit(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->map = NULL;
	map->tmpmap = NULL;
	map->map_x = 0;
	map->map_y = 0;
	map->map_s = 64;
	return (map);
}

t_pos	*posstructinit(t_data *data)
{
	t_pos	*p;

	p = (t_pos *)malloc(sizeof (t_pos));
	if (p == NULL)
		exit_failure("malloc error\n", data);
	p->color = 0;
	p->x = 0;
	p->y = 0;
	p->z = 0;
	return (p);
}

t_sprite	*sprite_struct_init(t_data *data, t_pos *pos, t_pos *mpos,
		double distance)
{
	t_sprite	*sprite;
	double		cosine;

	sprite = (t_sprite *)malloc(sizeof(t_sprite));
	if (sprite == NULL)
		exit_failure("malloc error\n", data);
	sprite->pos = pos;
	sprite->angle = calculate_angle(data, pos->x, pos->y);
	cosine = cos(sprite->angle);
	if (cosine <= 0.55)
		cosine = 0.55;
	sprite->distance = distance * (cosine);
	sprite->next = NULL;
	sprite->draw_start_x = 0;
	sprite->draw_end_x = 0;
	sprite->draw_start_y = 0;
	sprite->draw_end_y = 0;
	sprite->sprite_screen_x = 0;
	sprite->tx = 0;
	sprite->txoffset = 0;
	sprite->ty = 0;
	sprite->tyoffset = 0;
	sprite->x = mpos->x;
	sprite->y = mpos->y;
	return (sprite);
}

t_ray	ray_struct_init(void)
{
	t_ray	r;

	r.a = 0;
	r.x = 0;
	r.xo = 0;
	r.y = 0;
	r.yo = 0;
	r.txt = NULL;
	r.step = 0;
	r.toffset = 0;
	return (r);
}

t_rays	rays_struct_init(t_data *data)
{
	t_rays	r;

	r.h = ray_struct_init();
	r.p = posstructinit(data);
	r.t = ray_struct_init();
	r.texture = NULL;
	r.v = ray_struct_init();
	return (r);
}
