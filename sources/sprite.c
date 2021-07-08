/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:29:18 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/08 19:18:15 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	project_sprite(t_data *data, t_sprite *sprite, double lineH)
{
	sprite->sprite_screen_x = get_screen_x(data, sprite);
	sprite->draw_start_x = sprite->sprite_screen_x - lineH / 2;
	sprite->draw_end_x = sprite->draw_start_x + lineH;
	if (lineH > data->win_h)
		lineH = data->win_h;
	if (sprite->draw_end_x > data->win_w)
		sprite->draw_end_x = data->win_w;
	sprite->draw_start_y = (data->win_h / 2) - (lineH / 2);
	sprite->draw_end_y = sprite->draw_start_y + lineH;
}

void	draw_sprite_setup(t_data *data, t_sprite *s, double lineH)
{
	if (lineH > data->win_h)
		s->tyoffset = (lineH - data->win_h) / 2;
	if (s->draw_start_x < 0)
	{
		s->txoffset = - (s->draw_start_x);
		s->draw_start_x = 0;
	}
}

static void	draw(t_data *data, t_sprite *s, int i, int j)
{
	char	*src;

	src = data->sp_texture->addr + (int)s->ty * data->sp_texture
		->line_len + (int)s->tx * (data->sp_texture->bpp / 8);
	if (*(unsigned int *)src != 0xFF000000)
		*(unsigned int *)(data->img->addr + (j * data->img->line_len
					+ i * (data->img->bpp / 8))) = *(unsigned int *)src;
}

void	draw_sprite(t_data *data, t_sprite *s, t_raydist *rdist,
		double lineH)
{
	float	step;
	int		i;
	int		j;

	step = data->sp_texture->height / lineH;
	draw_sprite_setup(data, s, lineH);
	i = s->draw_start_x;
	s->tx = s->txoffset * step;
	while (i < s->draw_end_x)
	{
		j = s->draw_start_y;
		s->ty = s->tyoffset * step;
		while (j < s->draw_end_y && s->distance < rdist->td[i])
		{
			draw(data, s, i, j);
			s->ty += step;
			j++;
		}
		s->tx += step;
		i++;
	}
}

void	put_sprites(t_data *data, t_raydist *rdist)
{
	t_sprite	*current;
	double		lineH;

	current = data->sprite_head;
	while (current != NULL)
	{
		lineH = (data->map->map_s * data->win_h) / current->distance;
		project_sprite(data, current, lineH);
		draw_sprite(data, current, rdist, lineH);
		current = current->next;
	}
	free_sprites(&data->sprite_head);
}
