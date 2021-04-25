#include "../../cub3d.h"

static void	flood_fill(t_data *data, map_t map, int pos_x, int pos_y)
{
	if (pos_y >= (int)map.map_y || pos_y < 0)
		exit_failure("The map is not closed\n", data);
	else if (pos_x >= (int)map.map_x || pos_x < 0)
		exit_failure("The map is not closed\n", data);
	else if (map.map[pos_y][pos_x] != 0 && map.map[pos_y][pos_x] != 2)
		return ;
	if (map.map[pos_y][pos_x] == 0)
		map.map[pos_y][pos_x] = 9;
	else if (map.map[pos_y][pos_x] == 2)
		map.map[pos_y][pos_x] = 8;
	flood_fill(data, map, pos_x + 1, pos_y);
	flood_fill(data, map, pos_x - 1, pos_y);
	flood_fill(data, map, pos_x, pos_y + 1);
	flood_fill(data, map, pos_x, pos_y - 1);
}

static void	reset_map(map_t *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->map_y)
	{
		x = 0;
		while (x < map->map_x)
		{
			if (map->map[y][x] == 9)
				map->map[y][x] = 0;
			if (map->map[y][x] == 8)
				map->map[y][x] = 2;
			x++;
		}
		y++;
	}
}

void		check_layout(t_data *data, map_t *map, t_player *player)
{
	if (map->map_x < 3 || map->map_y < 3)
		exit_failure("The map is too small\n", data);
	if (player->x >= (int)map->map_x || player->x < 0)
		exit_failure("The coordinates are wrong\n", data);
	if (player->y >= (int)map->map_y || player->y < 0)
		exit_failure("The coordinates are wrong\n", data);
	flood_fill(data, *(map), (int)player->x, (int)player->y);
	reset_map(map);
}
