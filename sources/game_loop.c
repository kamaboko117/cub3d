/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:09:09 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/03 17:15:49 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <math.h>
#include "../cub3d.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		exit(0);
	}
	if (keycode == 119)
		data->inputs->w = 1;
	if (keycode == 97)
		data->inputs->a = 1;
	if (keycode == 115)
		data->inputs->s = 1;
	if (keycode == 100)
		data->inputs->d = 1;
	if (keycode == 65361)
		data->inputs->left = 1;
	if (keycode == 65363)
		data->inputs->right = 1;
}

int	key_realease_hook(int keycode, t_data *data)
{
	if (keycode == 119)
		data->inputs->w = 0;
	if (keycode == 97)
		data->inputs->a = 0;
	if (keycode == 115)
		data->inputs->s = 0;
	if (keycode == 100)
		data->inputs->d = 0;
	if (keycode == 65361)
		data->inputs->left = 0;
	if (keycode == 65363)
		data->inputs->right = 0;
}

int	render_next_frame(t_data *data)
{
	t_imgdata	*img;

	img = data->img;
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	imgdrawbg(img, data->win_w, data->win_h, data);
	moveplayer(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, img->img, 0, 0);
}

void	create_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, 2, 1L << 0, key_hook, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_realease_hook, data);
}

void	game_loop(t_data *data)
{
	t_imgdata	*img;

	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return ;
	data->mlx_win = mlx_new_window(data->mlx_ptr,
			 data->win_w, data->win_h, "CUB3D");
	if (data->mlx_win == NULL)
		return ;
	get_texture(data);
	create_hooks(data);
	img = imgstructinit();
	img->img = mlx_new_image(data->mlx_ptr, data->win_w, data->win_h);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	img->height = data->win_h;
	img->width = data->win_w;
	data->img = img;
	imgdrawbg(img, data->win_w, data->win_h, data);
	data->player->x = data->player->x * data->map->map_s + data->map->map_s / 2;
	data->player->y = data->player->y * data->map->map_s + data->map->map_s / 2;
	raycast(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, img->img, 0, 0);
	mlx_loop_hook(data->mlx_ptr, render_next_frame, data);
	mlx_loop(data->mlx_ptr);
}
