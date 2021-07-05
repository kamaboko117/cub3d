/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:11:25 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/05 19:46:02 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	display_keycode(int keycode, t_data *data)
{
	printf("%d\n", keycode);
}

int	display_button(int button, int x, int y, t_data *data)
{
	printf("press: %d, x: %d, y: %d\n", button, x, y);
}

int	display_buttonrelease(int button, int x, int y, t_data *data)
{
	printf("release: %d, x: %d, y: %d\n", button, x, y);
}

void	displaymaparray(t_map *map)
{
	int	i;
	int	j;
	int	k;

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
