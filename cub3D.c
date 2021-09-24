/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:52:20 by asaboure          #+#    #+#             */
/*   Updated: 2021/09/23 17:58:24 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "cub3d.h"
#include <mlx.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int	get_color_handle(char **rgb, t_data *data)
{
	int	r;
	int	g;
	int	b;
	int	color;

	color = 0;
	if (!rgb[0] || !rgb[1] || !rgb[2])
		exit_failure("Wrong data for the color\n", data);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
	{
		color = r;
		color = (color << 8) + g;
		color = (color << 8) + b;
	}
	else
		exit_failure("Wrong data for the color\n", data);
	return (color);
}

void	get_color(char *line, int *color, t_data *data)
{
	int		i;
	char	**rgb;

	i = 0;
	if (*color != -1)
		exit_failure("duplicate ceiling or floor color\n", data);
	*color = 0x0;
	while (line[i] && !ft_isdigit(line[i]))
	{
		if (line[i] == '-' && ft_isdigit(line[i + 1]))
			break ;
		i++;
	}
	rgb = ft_split(line + i, ',');
	*color = get_color_handle(rgb, data);
	free_split(rgb);
}

static void	cub3d(char *cub_path, int save, t_data *data)
{
	data->save = save;
	read_cub(cub_path, data);
	game_loop(data);
}

int	checkargs(char *cub_path, char *option, t_data *data)
{
	char	**path;
	int		path_len;

	path_len = 0;
	if (cub_path)
	{
		path = ft_split(cub_path, '.');
		while (path[path_len])
			path_len++;
		if (ft_strncmp(path[path_len - 1], "cub", 4))
			exit_failure("Wrong extension for the cub\n", data);
		free_split(path);
	}
	if (option)
	{
		if (ft_strncmp(option, "--save", 7))
			exit_failure("Wrong option\n", data);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data		*data;

	data = datainit();
	if (data == NULL)
	{
		puterror("failed to allocate memory for data structure\n");
		exit (EXIT_FAILURE);
	}
	if (argc > 3 || argc < 2)
		exit_failure("wrong number of arguments\n", data);
	else if (argc == 2 && !checkargs(argv[1], NULL, data))
		cub3d(argv[1], 0, data);
	else if (argc == 3 && !checkargs(argv[1], argv[2], data))
		cub3d(argv[1], 1, data);
	return (EXIT_SUCCESS);
}
