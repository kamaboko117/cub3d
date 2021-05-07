#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <math.h>
#include "../cub3d.h"

int		key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		exit(0);
	}
	if (keycode == 119)					//W
		data->inputs->w = 1;							
	if (keycode == 97)					//A
		data->inputs->a = 1;
	if (keycode == 115) 				//S
		data->inputs->s = 1;
	if (keycode == 100)					//D
		data->inputs->d = 1;
	if (keycode == 65361)				//left arrow
		data->inputs->left = 1;
	if (keycode == 65363)				//right arrow
		data->inputs->right = 1;
}

int		key_realease_hook(int keycode, t_data *data)
{
	if (keycode == 119)					//W
		data->inputs->w = 0;							
	if (keycode == 97)					//A
		data->inputs->a = 0;
	if (keycode == 115) 				//S
		data->inputs->s = 0;
	if (keycode == 100)					//D
		data->inputs->d = 0;
	if (keycode == 65361)				//left arrow
		data->inputs->left = 0;
	if (keycode == 65363)				//right arrow
		data->inputs->right = 0;
}

int		exit_cub3d(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(0);
}

int		render_next_frame(t_data *data)
{
	t_imgdata *img;

	img = data->img;
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	imgdrawbg(img, data->win_width, data->win_height, data);
//	imgdrawmap(img, data->map);
	moveplayer(data);
//	imgdrawplayer(img, data);
	raycast(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, img->img, 0, 0);
}

static void	set_texture(t_data *data, t_imgdata *texture)
{
	if (!(texture->img =
			mlx_xpm_file_to_image(data->mlx_ptr,
			texture->path,
			&texture->width,
			&texture->height)))
		exit_failure("Impossible to load a texture\n", data);
	texture->addr =
		mlx_get_data_addr(texture->img,
		&(texture->bits_per_pixel),
		&(texture->line_length),
		&(texture->endian));
	printf("%s\n, %d\n, %d\n", texture->path, texture->width, texture->height);
}

void		get_texture(t_data *data)
{
	set_texture(data, data->no_texture);
	set_texture(data, data->so_texture);
	set_texture(data, data->we_texture);
	set_texture(data, data->ea_texture);
//	if (data->sp_texture->path)
//		set_texture(data, data->sp_texture);
}

void	game_loop(t_data *data)
{
	t_imgdata	*img;
	
    if ((data->mlx_ptr = mlx_init()) == NULL)
		return;
    if ((data->mlx_win = mlx_new_window(data->mlx_ptr, data->win_width, data->win_height, "CUB3D")) == NULL)
		return;
	get_texture(data);
	mlx_hook(data->mlx_win, 2, 1L<<0, key_hook, data);
	mlx_hook(data->mlx_win, 3, 1L<<1, key_realease_hook, data);
	img->img = mlx_new_image(data->mlx_ptr, data->win_width, data->win_height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	img->height = data->win_height;
	img->width = data->win_width;
	data->img = img;
	imgdrawbg(img, data->win_width, data->win_height, data);
	data->player->x *= data->map->map_s;
	data->player->y *= data->map->map_s;
//	imgdrawmap(img, data->map);
//	imgdrawplayer(img, data);
	raycast(data);
//	printf("?\n");
//	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->no_texture->img, 0, 0);
//	printf("?\n");
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, img->img, 0, 0);
	mlx_loop_hook(data->mlx_ptr, render_next_frame, data);
	mlx_loop(data->mlx_ptr);
}