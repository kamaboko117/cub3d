/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:54:37 by asaboure          #+#    #+#             */
/*   Updated: 2021/08/06 21:44:44 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include "mlx.h"

void	puterror(char *str)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
}

void	clear_window(t_data *data)
{
	if (data->mlx_win)
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
}

void	exit_failure(char *error, t_data *data)
{
	clear_game(data);
	puterror(error);
	exit(EXIT_FAILURE);
}

void	clear_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->map->tmpmap)
		free(data->map->tmpmap);
	if (data->map->map)
	{
		while (i < data->map->map_y)
			free(data->map->map[i++]);
		free(data->map->map);
	}
	free(data->map);
}

void	clear_game(t_data *data)
{
	free(data->player);
	free(data->inputs);
	clear_map(data);
	clear_image(data->no_texture, data->mlx_ptr);
	clear_image(data->ea_texture, data->mlx_ptr);
	clear_image(data->so_texture, data->mlx_ptr);
	clear_image(data->we_texture, data->mlx_ptr);
	clear_image(data->sp_texture, data->mlx_ptr);
	clear_image(data->img, data->mlx_ptr);
	if (data->sprite_head)
		free_sprites(&data->sprite_head);
	free(data->sprite_head);
	clear_window(data);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free(data);
}

void	clear_image(t_imgdata *img, void *mlx)
{
	if (img->path)
		free(img->path);
	if (img->img)
		mlx_destroy_image(mlx, img->img);
	free (img);
}
