#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <math.h>
#include "cub3d.h"

int		key_hook(int keycode, data_t *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		exit(0);
	}
	if (keycode == 119)					//W
		data->inputs[0] = 1;							
	if (keycode == 97)					//A
		data->inputs[1] = 1;
	if (keycode == 115) 				//S
		data->inputs[2] = 1;
	if (keycode == 100)					//D
		data->inputs[3] = 1;
	if (keycode == 65361)				//left arrow
		data->inputs[4] = 1;
	if (keycode == 65363)				//right arrow
		data->inputs[5] = 1;
}

int		key_realease_hook(int keycode, data_t *data)
{
	if (keycode == 119)					//W
		data->inputs[0] = 0;							
	if (keycode == 97)					//A
		data->inputs[1] = 0;
	if (keycode == 115) 				//S
		data->inputs[2] = 0;
	if (keycode == 100)					//D
		data->inputs[3] = 0;
	if (keycode == 65361)				//left arrow
		data->inputs[4] = 0;
	if (keycode == 65363)				//right arrow
		data->inputs[5] = 0;
}

int		exit_cub3d(data_t *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(0);
}

int		render_next_frame(data_t *data)
{
	imgdata_t img;

	img = data->img;
//	imgdrawbg(&img, 1024, 512, 0x0000FF00);
	imgdrawmap(&img, &data->map);
	moveplayer(data);
	imgdrawplayer(&img, data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, img.img, 0, 0);
}

int main(void)
{
    data_t		data;
	player_t	player;
	imgdata_t	img;
	
	player.x = 64;
	player.y = 64;
	player.a = M_PI;
	data.player = player;
	arrayinit(&data);
	printf("x: %f | y: %f\n", data.player.x, data.player.y);
    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 1024, 512, "Hello world")) == NULL)
        return (EXIT_FAILURE);
//	mlx_key_hook(data.mlx_win, display_button, &data);
//	mlx_mouse_hook(data.mlx_win, display_button, &data);
	mlx_hook(data.mlx_win, 17, 1L<<17, exit_cub3d, &data);
//	mlx_hook(data.mlx_win, 2, 1L<<0, display_button, &data);				//show pressed buton
//	mlx_hook(data.mlx_win, 3, 1L<<1, display_buttonrelease, &data);			//show released button
	mlx_hook(data.mlx_win, 2, 1L<<0, key_hook, &data);
	mlx_hook(data.mlx_win, 3, 1L<<1, key_realease_hook, &data);
//	mlx_hook(data.mlx_win, 6, 1L<<6, display_button, &data);

	img.img = mlx_new_image(data.mlx_ptr, 1024, 512);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	data.img = img;
	data.map = mapinit(&data);
	displaymaparray(&data.map);
	printf("last: %d\n", data.map.map[61]);
	printf("mapS: %d, mapX: %d, mapY: %d\n", data.map.map_s, data.map.map_x, data.map.map_y);
//	printf("data.img.img: %p, img.img: %p\n", data.img.img, img.img);
//	imgdrawbg(&img, 1024, 512, 0x0000FF00);
	imgdrawmap(&img, &data.map);
	imgdrawplayer(&img, &data);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, img.img, 0, 0);
	mlx_loop_hook(data.mlx_ptr, render_next_frame, &data);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}