#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

typedef struct	player_s
{
	int	x;
	int	y;
}				player_t;

typedef struct	map_s
{
	int	map_x;
	int	map_y;
	int	map_s;
	int map[64];
}				map_t;

typedef struct imgdata_s
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				imgdata_t;

typedef struct	data_s
{
    void		*mlx_ptr;
    void		*mlx_win;
	player_t	player;
	imgdata_t	img;
	map_t		map;
}                 data_t;


int	key_hook(int keycode, data_t *data)
{

	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		exit(0);
	}
	if (keycode == 119)
		data->player.y--;
	if (keycode == 97)
		data->player.x--;
	if (keycode == 115)
		data->player.y++;
	if (keycode == 100)
		data->player.x++;
	printf("x: %d | y: %d\n", data->player.x, data->player.y);
}

int display_keycode(int keycode, data_t *data)
{
	printf("%d\n", keycode);
}

int display_button(int button, int x, int y, data_t *data)
{
	printf("%d, x: %d, y: %d\n", button, x, y);
}

int	exit_cub3d(data_t *data)
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

void	imgputsquare(imgdata_t *img, int x, int y, int color)
{
	int	len;
	int wid;

	printf("x: %d, y: %d\n", x, y);
	wid = 64;
	while (wid)
	{
		len = 64;
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

int		render_next_frame(data_t *data)
{
	imgdata_t img;

	img = data->img;
	imgdrawbg(&img, 1024, 512, 0x0000FF00);
	imgputsquare(&img, data->player.x, data->player.y, 0x00FF0000);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, img.img, 0, 0);
}


void	displaymaparray(map_t *map)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	printf("map: ");
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
	printf("map_y = %d\n", map->map_y);
	while(y < map->map_y)
	{
		x = 0;
		while(x < map->map_x)
		{
			color = 0x002C2F33;
			if (map->map[y * map->map_x + x] == 1)
				color = 0x007289DA;
			imgputsquare(img, x * map->map_s, y * map->map_s, color);
			x++;			
		}
		y++;
	}
	int i;
	int j;

	i = 0;
	displaymaparray(map);
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

int main(void)
{
    data_t		data;
	player_t	player;
	imgdata_t	img;
	
	player.x = 5;
	player.y = 5;
	data.player = player;
	printf("x: %d | y: %d\n", data.player.x, data.player.y);
    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 1024, 512, "Hello world")) == NULL)
        return (EXIT_FAILURE);
//	mlx_key_hook(data.mlx_win, display_button, &data);
//	mlx_mouse_hook(data.mlx_win, display_button, &data);
	mlx_hook(data.mlx_win, 17, 1L<<17, exit_cub3d, &data);
	mlx_hook(data.mlx_win, 2, 1L<<0, key_hook, &data);
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
	imgputsquare(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, img.img, 0, 0);

//	mlx_loop_hook(data.mlx_ptr, render_next_frame, &data);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}