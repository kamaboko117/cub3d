#include "../../cub3d.h"
#include "../../libft/libft.h"

static int	ft_ismap_char(char c)
{
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (1);
	else if (c == '0' || c == '1' || c == '2' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

static void	check_dimensions(int *width, int *height)
{
	if (*width < 480)
		*width = 480;
	if (*height < 320)
		*height = 320;
	if (*width >= 2560)
		*width = 2560;
	if (*height >= 1440)
		*height = 1440;
}

static void	check_texture(t_data *data, char *texture_path)
{
	char	**path;
	int		len;

	if (!texture_path)
		exit_failure("Missing texture\n", data);
	len = 0;
	path = ft_split(texture_path, '.');
	while (path[len])
		len++;
	if (ft_strcmp(path[len - 1], "xpm"))
	{
		free_split(path);
		exit_failure("Wrong extension for xpm file\n", data);
	}
	free_split(path);
}

static void	check_map(t_data *data)
{
	int	i;

	if (!data->map)
		exit_failure("Missing map layout\n", data);
	else
	{
		i = 0;
		while (data->map->tmpmap[i])
		{
			if (!ft_ismap_char(data->map->tmpmap[i]))
				exit_failure("Wrong characters in the map layout\n", data);
			if (data->map->tmpmap[i] == '2'
				&& data->sp_texture->path == NULL)
				exit_failure("The sprite texture doesn't exist\n", data);
			i++;
		}
		if (data->player->dir == '0')
			exit_failure("No player in map\n", data);
	}
}

void	check_cub_data(t_data *data)
{
	if (data->win_h == 0 || data->win_w == 0)
	{
		clear_game(data);
		exit_failure("Resolution missing\n", data);
	}
	check_dimensions(&(data->win_w), &(data->win_h));
	check_texture(data, data->no_texture->path);
	check_texture(data, data->so_texture->path);
	check_texture(data, data->we_texture->path);
	check_texture(data, data->ea_texture->path);
	if (data->sp_texture->path)
		check_texture(data, data->sp_texture->path);
	check_map(data);
}
