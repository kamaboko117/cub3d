#include "../../cub3d.h"
#include <mlx.h>

void	set_position(t_player *player, float pos_x, float pos_y)
{
	player->x = pos_x;
	player->y = pos_y;
}

void	free_split(char **str)
{
	int	len;

	len = 0;
	while (str[len])
		free(str[len++]);
	free(str);
}

int	exit_cub3d(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(0);
}
