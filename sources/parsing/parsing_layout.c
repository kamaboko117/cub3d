#include "../../cub3d.h"
#include "../../libft/libft.h"

int	*get_row(char *line, t_data *data, int current_row)
{
	int	*row;
	int	i;

	if (!(row = (int *)malloc(sizeof(int) * data->map->map_x)))
		return (NULL);
	i = 0;
	while (i < data->map->map_x)
	{
		while (line[i])
		{
			if (isdirection(line[i]))
			{
				set_position(data->player, i, current_row);
				row[i] = 0;
			}
			else
				row[i] = ft_isdigit(line[i]) ? line[i] - '0' : 0;
			i++;
		}
		while (i < data->map->map_x)
			row[i++] = 0;
	}
	return (row);
}

void		get_layout(t_data *data)
{
	char		**split_map;
	map_t		*map;
	int			i;

	map = data->map;
	split_map = ft_split(map->tmpmap, '\n');
	while (split_map[(int)map->map_y])
	{
		if (map->map_x < (int)ft_strlen(split_map[map->map_y]))
			map->map_x = (int)ft_strlen(split_map[map->map_y]);
		map->map_y++;
	}
	if (!(map->map = (int **)malloc(map->map_y * sizeof(int *))))
		return ;
	i = 0;
	while (i < map->map_y)
	{
		map->map[i] = get_row(split_map[i], data, i);
		i++;
	}
	free_split(split_map);
}
