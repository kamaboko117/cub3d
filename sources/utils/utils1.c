#include "../../cub3d.h"

void	set_position(t_player *player, float pos_x, float pos_y)
{
	player->x += pos_x;
	player->y += pos_y;
}

void	free_split(char **str)
{
	int	len;

	len = 0;
	while (str[len])
		free(str[len++]);
	free(str);
}
