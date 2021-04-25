#include "../cub3d.h"

void	forward(t_player *player, int velocity)
{
	player->x += player->dx * velocity;
	player->y += player->dy * velocity;
}

void	backward(t_player *player, int velocity)
{
	player->x -= player->dx * velocity;
	player->y -= player->dy * velocity;
}

void	left(t_player *player, int velocity)
{
	player->x += player->dxleft * velocity;
	player->y += player->dyleft * velocity;
}

void	right(t_player *player, int velocity)
{
	player->x -= player->dxleft * velocity;
	player->y -= player->dyleft * velocity;
}

void	moveplayer(t_data *data)
{
	int		velocity;
	double	sensitivity;

	velocity = 1;
	sensitivity = 0.01;
	if (data->inputs->w == 1)
		forward(data->player, velocity);
	if (data->inputs->a == 1)
		left(data->player, velocity);
	if (data->inputs->s == 1) 
		backward(data->player, velocity);
	if (data->inputs->d == 1)
		right(data->player, velocity);
	if (data->inputs->left == 1)
		lookleft(data->player, sensitivity);
	if (data->inputs->right == 1)
		lookright(data->player, sensitivity);
	printf("x: %f | y: %f | a: %f\n", data->player->x, data->player->y, data->player->a);
}
