/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermovement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:00:54 by asaboure          #+#    #+#             */
/*   Updated: 2021/08/11 19:04:38 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	forward(t_player *player, int velocity, t_data *data)
{
	if (!checkcollision(player->x + player->dx * velocity, player->y, data))
		player->x += player->dx * velocity;
	if (!checkcollision(player->x, player->y + player->dy * velocity, data))
		player->y += player->dy * velocity;
}

void	backward(t_player *player, int velocity, t_data *data)
{
	if (!checkcollision(player->x - player->dx * velocity, player->y, data))
		player->x -= player->dx * velocity;
	if (!checkcollision(player->x, player->y - player->dy * velocity, data))
		player->y -= player->dy * velocity;
}

void	left(t_player *player, int velocity, t_data *data)
{
	if (!checkcollision(player->x + player->dxleft * velocity, player->y, data))
		player->x += player->dxleft * velocity;
	if (!checkcollision(player->x, player->y + player->dyleft * velocity, data))
		player->y += player->dyleft * velocity;
}

void	right(t_player *player, int velocity, t_data *data)
{
	if (!checkcollision(player->x - player->dxleft * velocity, player->y, data))
		player->x -= player->dxleft * velocity;
	if (!checkcollision(player->x, player->y - player->dyleft * velocity, data))
		player->y -= player->dyleft * velocity;
}

void	moveplayer(t_data *data)
{
	int		velocity;
	double	sensitivity;

	velocity = 3;
	sensitivity = 0.05;
	if (data->inputs->w == 1)
		forward(data->player, velocity, data);
	if (data->inputs->a == 1)
		left(data->player, velocity, data);
	if (data->inputs->s == 1)
		backward(data->player, velocity, data);
	if (data->inputs->d == 1)
		right(data->player, velocity, data);
	if (data->inputs->left == 1)
		lookleft(data->player, sensitivity);
	if (data->inputs->right == 1)
		lookright(data->player, sensitivity);
}
