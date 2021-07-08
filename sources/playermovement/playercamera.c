/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playercamera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:04:56 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/06 18:04:56 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	lookleft(t_player *player, double sensitivity)
{
	player->a -= sensitivity;
	if (player->a < 0)
		player->a += 2 * M_PI;
	player->dx = cos(player->a);
	player->dy = sin(player->a);
	player->dxleft = cos(player->a - (M_PI / 2));
	player->dyleft = sin(player->a - (M_PI / 2));
}

void	lookright(t_player *player, double sensitivity)
{
	player->a += sensitivity;
	if (player->a > 2 * M_PI)
		player->a -= 2 * M_PI;
	player->dx = cos(player->a);
	player->dy = sin(player->a);
	player->dxleft = cos(player->a - (M_PI / 2));
	player->dyleft = sin(player->a - (M_PI / 2));
}
