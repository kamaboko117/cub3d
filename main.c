#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

typedef struct	data_s
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 data_t;

int	close(int keycode, data_t data)
{
	if (keycode == 65307)
		mlx_destroy_window(data.mlx_ptr, data.mlx_win);
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

int main(void)
{
    data_t        data;

    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 640, 480, "Hello world")) == NULL)
        return (EXIT_FAILURE);
//	mlx_key_hook(data.mlx_win, close, &data);
//	mlx_mouse_hook(data.mlx_win, display_button, &data);
	mlx_hook(data.mlx_win, 17, 1L<<17, exit_cub3d, &data);
	mlx_hook(data.mlx_win, 2, 1L<<0, close, &data);
	mlx_hook(data.mlx_win, 6, 1L<<6, display_button, &data);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}