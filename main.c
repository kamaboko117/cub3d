#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <math.h>
#include "cub3d.h"

void	forward(player_t *player, int velocity)
{
	player->x += player->dx * velocity;
	player->y += player->dy * velocity;
}

void	backward(player_t *player, int velocity)
{
	player->x -= player->dx * velocity;
	player->y -= player->dy * velocity;
}

void	lookleft(player_t *player, double sensitivity)
{
	player->a -= sensitivity;
	if (player->a < 0) 
		player->a += 2 * M_PI;
	player->dx = cos(player->a);
	player->dy = sin(player->a);
	player->dxleft = cos(player->a - (M_PI / 2));
	player->dyleft = sin(player->a - (M_PI / 2));
}

void	lookright(player_t *player, double sensitivity)
{
	player->a += sensitivity;
	if (player->a > 2 * M_PI) 
		player->a -= 2 * M_PI;
	player->dx = cos(player->a);
	player->dy = sin(player->a);
	player->dxleft = cos(player->a - (M_PI / 2));
	player->dyleft = sin(player->a - (M_PI / 2));
}

void	left(player_t *player, int velocity)
{
	player->x += player->dxleft * velocity;
	player->y += player->dyleft * velocity;
}

void	right(player_t *player, int velocity)
{
	player->x -= player->dxleft * velocity;
	player->y -= player->dyleft * velocity;
}

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

void	moveplayer(data_t *data)
{
	int		velocity;
	double	sensitivity;

	velocity = 1;
	sensitivity = 0.03;
	if (data->inputs[0] == 1)
		forward(&data->player, velocity);
	if (data->inputs[1] == 1)
		left(&data->player, velocity);
	if (data->inputs[2] == 1) 
		backward(&data->player, velocity);
	if (data->inputs[3] == 1)
		right(&data->player, velocity);
	if (data->inputs[4] == 1)
		lookleft(&data->player, sensitivity);
	if (data->inputs[5] == 1)
		lookright(&data->player, sensitivity);
	printf("x: %f | y: %f | a: %f\n", data->player.x, data->player.y, data->player.a);
}

int 	display_keycode(int keycode, data_t *data)
{
	printf("%d\n", keycode);
}

int 	display_button(int button, int x, int y, data_t *data)
{
	printf("press: %d, x: %d, y: %d\n", button, x, y);
}

int 	display_buttonrelease(int button, int x, int y, data_t *data)
{
	printf("release: %d, x: %d, y: %d\n", button, x, y);
}

int		exit_cub3d(data_t *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(0);
}

void	imgputpixel(imgdata_t *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	imgputsquare(imgdata_t *img, int size, int x, int y, int color)
{
	int	len;
	int wid;

//	printf("x: %d, y: %d\n", x, y);
	wid = size;
	while (wid)
	{
		len = size;
		while (len)
		{
			imgputpixel(img, x + len, y + wid, color);
			len--;
		}
		wid--;
	}
}

void	imgdrawbg(imgdata_t *img, int xres, int yres, int color)
{
	int	i;
	
	while(xres)
	{
		i = yres;
		while(i)
		{
			imgputpixel(img, xres, i, color);
			i--;
		}
		xres--;
	}
}

void	displaymaparray(map_t *map)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	printf("map:\n");
	while(i < 8)
	{
		j = 0;
		while (j++ < 8)
		{
			printf("%d, ", map->map[k]);
			k++;
		}
		printf("\n");
		i++; 
	printf("\n");
	}
}

void	imgdrawmap(imgdata_t *img, map_t *map)
{
	int	y;
	int x;
	int	color;

	y = 0;
	while(y < map->map_y)
	{
		x = 0;
		while(x < map->map_x)
		{
			color = 0x002C2F33;
			if (map->map[y * map->map_x + x] == 1)
				color = 0x007289DA;
			imgputsquare(img, map->map_s, x * map->map_s, y * map->map_s, color);
			x++;			
		}
		y++;
	}
}

void	imgdrawplayer(imgdata_t *img, data_t *data)
{
	t_pos	start;
	t_pos	end;

	start.color = 0xFFFF00;
	start.x = data->player.x + 4;
	start.y = data->player.y + 4;
	end.x = start.x + 10 * cos(data->player.a);
	end.y = start.y + 10 * sin(data->player.a);
	
//	printf("%f\n", data->player.a);
//	printf("start: %d, %d | end: %d, %d\n", start.x, start.y, end.x, end.y);
	imgputsquare(img, 8, data->player.x, data->player.y, 0x00FF0000);
	imgdrawline(start, end, data);
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