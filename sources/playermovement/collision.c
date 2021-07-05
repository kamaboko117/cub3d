/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:02:20 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/05 19:02:45 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	checkcollision(double x, double y, t_data *data)
{
	x = x / data->map->map_s;
	y = y / data->map->map_s;
	if (data->map->map[(int)y][(int)x] >= 1)
		return (1);
	return (0);
}
