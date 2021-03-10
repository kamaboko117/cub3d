#include "../cub3d.h"

map_t	mapinit(data_t *data)
{
	map_t	map;
	int		i;
	int		layout[] =
	{
		1,1,1,1,1,1,1,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,1,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,
	};

	map.map_s = 64;
	map.map_x = 8;
	map.map_y = 8;
	i = 0;
	while(i < map.map_s)
	{
		map.map[i] = layout[i];
		i++;
	}
	displaymaparray(&map);
	return (map);
}

void	arrayinit(data_t *data)
{
	int	i;

	i = 0;
	while(i < 10)
	{
		data->inputs[i] = 0;
		i++;
	}
}
