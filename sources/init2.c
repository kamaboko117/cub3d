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

t_pos	*posstructinit()
{
	t_pos	*p;

	if (!(p = (t_pos *)malloc(sizeof (t_pos))))
		return (NULL);
	p->color = 0;
	p->x = 0;
	p->y = 0;
	p->z = 0;
	return (p);
}
