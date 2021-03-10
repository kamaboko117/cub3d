#include "../cub3d.h"

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
