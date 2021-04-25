#include "../cub3d.h"
#include "../libft/libft.h"
#include "mlx.h"

void	puterror(char *str)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
}

void	exit_failure(char *error, t_data *data)
{
	clear_game(data);
	puterror(error);
	exit(EXIT_FAILURE);
}

void	clear_game(t_data *data)
{
	free (data->player);
	free (data->inputs);
//	clear_map(data);
	clear_image(data->no_texture, data->mlx_win, data->mlx_ptr);
	clear_image(data->ea_texture, data->mlx_win, data->mlx_ptr);
	clear_image(data->so_texture, data->mlx_win, data->mlx_ptr);
	clear_image(data->we_texture, data->mlx_win, data->mlx_ptr);
	clear_image(data->img, data->mlx_win, data->mlx_ptr);
	free (data);
}

void	clear_image(t_imgdata *img, void *win, void *mlx)
{
	if (img->path)
		free(img->path);
	if (img->addr)
		mlx_destroy_image(mlx, win);
	free (img);
}
