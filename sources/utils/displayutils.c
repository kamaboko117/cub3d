/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:11:25 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/08 19:24:14 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	display_keycode(int keycode)
{
	printf("%d\n", keycode);
	return (1);
}

int	display_button(int button, int x, int y)
{
	printf("press: %d, x: %d, y: %d\n", button, x, y);
	return (1);
}

int	display_buttonrelease(int button, int x, int y)
{
	printf("release: %d, x: %d, y: %d\n", button, x, y);
	return (1);
}

void	displaymaparray(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	printf("map:\n");
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			printf("%d, ", map->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
		printf("\n");
	}
}
