#include "../../cub3d.h"

void	imgdrawtexturecol(t_pos a, t_pos b, t_data *data, t_imgdata *texture, float step)
{
	int	i;
	char	*src;
	float	ty;

	i = a.y;
	ty = 0;
	while (i < b.y)
	{
		src = texture->addr + ((int)ty * texture->line_length);
		*(unsigned int*)(data->img->addr + (i * data->img->line_length + a.x * (data->img->bits_per_pixel / 8))) = *(unsigned int*)src;
		ty += step;
		i++;
	}
}

void	draw_walls(t_data *data, t_raydist rdist, int r, t_imgdata *texture)
{
	t_pos	a;
	t_pos	b;
	float	lineH;
	float	lineO;
	float	step;
	int		i;
	
	lineH = (data->map->map_s * data->win_height)/ rdist.tdist;
	if (lineH > data->win_height)
		lineH = data->win_height;
	lineO = data->win_height / 2 - lineH / 2;
	a.x = 16 * r;
	b.x = 16 * r;
	a.y = lineO;
	b.y = lineH + lineO;
	i = 0;
	step = 32 / lineH;
	while(i < 16)
	{
		imgdrawtexturecol(a, b, data, texture, step);
		a.x += 1;
		b.x += 1;
		i++;
	}
}

void	imgdrawray(t_data *data, t_ray *r, int color)
{
	t_pos	a;
	t_pos	b;


	a.x = (int)data->player->x;
	a.y = (int)data->player->y;
	b.x = (int)r->x;
	b.y = (int)r->y;
	a.color = color;
	imgdrawline(a, b, data);
}
