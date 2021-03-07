#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

typedef struct	player_s
{
	int	x;
	int	y;
}				player_t;

typedef struct	data_s
{
    void		*mlx_ptr;
    void		*mlx_win;
	player_t	player;
}                 data_t;

typedef struct imgdata_s
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				imgdata_t;

int	key_hook(int keycode, data_t *data)
{
	printf("player's y pos: %d\n", data->player.y);
	if (keycode == 65307)
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	if (keycode == 119)
		data->player.y++;
	if (keycode == 97)
		data->player.x--;
	if (keycode == 115)
		data->player.y--;
	if (keycode == 100)
		data->player.x++;
}

int display_keycode(int keycode, data_t data)
{
	printf("%d\n", keycode);
}

int display_button(int button, int x, int y, data_t data)
{
	printf("%d, x: %d, y: %d\n", button, x, y);
}

int	exit_cub3d(data_t data)
{
	mlx_destroy_window(data.mlx_ptr, data.mlx_win);
	exit(0);
}

int	render_next_frame(player_t player, data_t data)
{
	int	rgb;

	rgb = 255;
	rgb = (rgb << 8) + 0;
	rgb = (rgb << 8) + 0;

	printf("mdr\n");
	//mlx_pixel_put(data.mlx_ptr, data.mlx_win, player.x, player.y, rgb);
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

	wid = 5;
	while (wid)
	{
		len = 5;
		while (len)
		{
			imgputpixel(img, x + len, y + wid, color);
			len--;
		}
		wid--;
	}
}

int main(void)
{
    data_t		data;
	player_t	player;
	imgdata_t	img;

	player.x = 5;
	player.y = 5;
	data.player = player;
	printf("player's y pos: %d\n", data.player.y);
    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 640, 480, "Hello world")) == NULL)
        return (EXIT_FAILURE);
//	mlx_key_hook(data.mlx_win, display_button, &data);
//	mlx_mouse_hook(data.mlx_win, display_button, &data);
	mlx_hook(data.mlx_win, 17, 1L<<17, exit_cub3d, &data);
	mlx_hook(data.mlx_win, 2, 1L<<0, key_hook, &data);
//	mlx_hook(data.mlx_win, 6, 1L<<6, display_button, &data);

	img.img = mlx_new_image(data.mlx_ptr, 640, 480);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	imgputsquare(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, img.img, 0, 0);

//	mlx_loop_hook(data.mlx_ptr, render_next_frame, &);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}