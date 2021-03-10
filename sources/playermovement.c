#include "../cub3d.h"

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
