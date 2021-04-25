#include "../../cub3d.h"
#include "../../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void	get_texture_path(char *line, t_imgdata *texture)
{
	char	**path;

	path = ft_split(line, ' ');
	if (path[1])
		texture->path = ft_strdup(path[1]);
	free_split(path);
}

static void	get_map(char *line, t_data *data)
{
	int	i;

	ft_strjoin_free(&(data->map->tmpmap), line);
	ft_strjoin_free(&(data->map->tmpmap), "\n");
	i = -1;
	while (line[++i])
	{
		if (isdirection(line[i]))
		{
			if (data->player->dir == '0')
			{
				data->player->dir = line[i];
				init_player(data);
			}
			else
				exit_failure("Map has more than one player\n", data);
		}
	}
}

static void	get_data(char *line, t_data *data)
{
	char	*trim;

	trim = ft_strtrim(line, " ");
	if (!ft_strncmp(trim, "R", 1))
		get_resolution(line, &data->win_width, &data->win_height);
	else if (!ft_strncmp(trim, "NO", 2))
		get_texture_path(line, data->no_texture);
	else if (!ft_strncmp(trim, "EA", 2))
		get_texture_path(line, data->ea_texture);
	else if (!ft_strncmp(trim, "SO", 2))
		get_texture_path(line, data->so_texture);
	else if (!ft_strncmp(trim, "WE", 2))
		get_texture_path(line, data->we_texture);
	else if (!ft_strncmp(trim, "C", 1))
		get_color(trim, &(data->c_color), data);
	else if (!ft_strncmp(trim, "F", 1))
		get_color(trim, &(data->f_color), data);
	free(trim);
}

void		get_cub_data(char *line, t_data *data)
{
	if(data->map_started == 1)
	{
		if(data->map_stopped == 1 && !isempty(line))
			exit_failure("Map has a format error 1\n", data);
		else
		{
			if (isempty(line))
				data->map_stopped = 1;
			else if (isrow(line))
				get_map(line, data);
			else if (data->map_started == 1)
				exit_failure("Map has a format error\n", data);
		}	
	}
	else
	{
		if (isrow(line))
		{
			data->map_started = 1;
			get_map(line, data);
		}
		else
			get_data(line, data);
	}
}

void		read_cub(char *cub_path, t_data *data)
{
	int			fd;
	char		*line;

	printf("reading cub\n");
	if ((fd = open(cub_path, O_RDONLY)) < 0)
		exit_failure("The file doesn't exist\n", data);
	else
	{
		while (get_next_line(fd, &line) > 0)
		{
			get_cub_data(line, data);
			printf("%s\n", line);
			free(line);
		}
		get_cub_data(line, data);
		printf("checking cub data\n");
		free(line);
		check_cub_data(data);
		get_layout(data);
		check_layout(data, data->map, data->player);
	}
}