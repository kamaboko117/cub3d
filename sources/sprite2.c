/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:32:24 by asaboure          #+#    #+#             */
/*   Updated: 2021/08/13 16:45:50 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	sorted_insert(t_sprite **head_ref, t_sprite *new_node)
{
	t_sprite	*current;

	if ((*head_ref) == NULL || (*head_ref)->distance <= new_node->distance)
	{
		new_node->next = (*head_ref);
		(*head_ref) = new_node;
	}
	else
	{
		current = (*head_ref);
		while (current->next != NULL
			&& current->next->distance >= new_node->distance)
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}

int	get_screen_x(t_data *data, t_sprite *sprite)
{
	int		i;
	float	angle;
	double	dr;

	angle = sprite->angle;
	angle = angle / DR;
	i = data->win_w / 2;
	dr = (80 / (double)data->win_w);
	i += angle / dr;
	return (i);
}

void	is_sprite(t_data *data, t_pos *m)
{
	t_pos		*newpos;
	t_sprite	*new_sprite;
	t_sprite	*current;
	double		distance;

	newpos = posstructinit(data);
	newpos->x = m->x * data->map->map_s + data->map->map_s / 2;
	newpos->y = m->y * data->map->map_s + data->map->map_s / 2 ;
	current = data->sprite_head;
	while (current != NULL)
	{
		if (current->x == m->x
			&& current->y == m->y)
		{
			free(newpos);
			return ;
		}
		current = current->next;
	}
	distance = dist(newpos, data->player->x, data->player->y);
	new_sprite = sprite_struct_init(data, newpos, m, distance);
	sorted_insert(&(data->sprite_head), new_sprite);
	free(newpos);
}
