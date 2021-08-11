/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:05:14 by asaboure          #+#    #+#             */
/*   Updated: 2021/08/11 18:28:34 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"
#include <mlx.h>

void	set_position(t_player *player, float pos_x, float pos_y)
{
	player->x = pos_x;
	player->y = pos_y;
}

void	free_split(char **str)
{
	int	len;

	len = 0;
	while (str[len])
		free(str[len++]);
	free(str);
}

int	exit_cub3d(t_data *data)
{
	clear_game(data);
	exit(EXIT_SUCCESS);
}

double	ray_dist(t_player *a, t_ray *b)
{
	return (sqrt((b->x - a->x) * (b->x - a->x)
			+ (b->y - a->y) * (b->y - a->y)));
}

double	dist(t_pos *a, int x, int y)
{
	return (sqrt((x - a->x) * (x - a->x) + (y - a->y) * (y - a->y)));
}
