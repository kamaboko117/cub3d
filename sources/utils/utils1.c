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

double	ray_dist(t_player *a, t_ray *b)
{
	return (sqrt((b->x - a->x) * (b->x - a->x)
			+ (b->y - a->y) * (b->y - a->y)));
}

double	dist(t_pos *a, int x, int y)
{
	return (sqrt((x - a->x) * (x - a->x) + (y - a->y) * (y - a->y)));
}
