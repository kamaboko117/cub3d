#include "../cub3d.h"

t_imgdata	*imgstructinit(void)
{
	t_imgdata	*img;

	img = (t_imgdata *)malloc(sizeof(t_imgdata));
	if (img == NULL)
		return (NULL);
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->endian = 0;
	img->line_len = 0;
	img->path = NULL;
	img->width = 0;
	img->height = 0;
	return (img);
}

t_player	*playerstructinit(void)
{
	t_player	*p;

	p = (t_player *)malloc(sizeof(t_player));
	if (p == NULL)
		return (NULL);
	p->x = 0;
	p->y = 0;
	p->a = 0;
	p->dx = 0;
	p->dy = 0;
	p->dxleft = 0;
	p->dyleft = 0;
	p->dir = '0';
	return (p);
}

t_inputs	*inputstructinit(void)
{
	t_inputs	*inputs;

	inputs = (t_inputs *)malloc(sizeof (t_inputs));
	if (inputs == NULL)
		return (NULL);
	inputs->a = 0;
	inputs->d = 0;
	inputs->left = 0;
	inputs->right = 0;
	inputs->s = 0;
	inputs->w = 0;
	return (inputs);
}

t_data	*datainit(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->map_started = 0;
	data->map_stopped = 0;
	data->save = 0;
	data->c_color = 0;
	data->f_color = 0;
	data->sprite_head = NULL;
	if (!(data->no_texture = imgstructinit())
		|| !(data->ea_texture = imgstructinit())
		|| !(data->so_texture = imgstructinit())
		|| !(data->we_texture = imgstructinit())
		|| !(data->sp_texture = imgstructinit())
		|| !(data->img = imgstructinit())
		|| !(data->player = playerstructinit())
		|| !(data->map = mapstructinit())
		|| !(data->inputs = inputstructinit()))
		return (NULL);
	return (data);
}

void	init_player(t_data *data)
{
	if (data->player->dir == 'N')
		data->player->a = M_PI / 2;
	if (data->player->dir == 'E')
		data->player->a = 0;
	if (data->player->dir == 'S')
		data->player->a = M_PI + (M_PI / 2);
	if (data->player->dir == 'W')
		data->player->a = M_PI;
}
