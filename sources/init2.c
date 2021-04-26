#include "../cub3d.h"

map_t	*mapstructinit()
{
	map_t *map;

	if (!(map = (map_t *)malloc(sizeof(map_t))))
		return (NULL);
	map->map = NULL;
	map->tmpmap = NULL;
	map->map_x = 0;
	map->map_y = 0;
	map->map_s = 64;
	return (map);
}