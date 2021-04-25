#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <math.h>
#include "cub3d.h"

int		key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		exit(0);
	}
	if (keycode == 119)					//W
		data->inputs[0] = 1;							
	if (keycode == 97)					//A
		data->inputs[1] = 1;
	if (keycode == 115) 				//S
		data->inputs[2] = 1;
	if (keycode == 100)					//D
		data->inputs[3] = 1;
	if (keycode == 65361)				//left arrow
		data->inputs[4] = 1;
	if (keycode == 65363)				//right arrow
		data->inputs[5] = 1;
}

int		key_realease_hook(int keycode, t_data *data)
{
	if (keycode == 119)					//W
		data->inputs[0] = 0;							
	if (keycode == 97)					//A
		data->inputs[1] = 0;
	if (keycode == 115) 				//S
		data->inputs[2] = 0;
	if (keycode == 100)					//D
		data->inputs[3] = 0;
	if (keycode == 65361)				//left arrow
		data->inputs[4] = 0;
	if (keycode == 65363)				//right arrow
		data->inputs[5] = 0;
}

int		exit_cub3d(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(0);
}

int		render_next_frame(t_data *data)
{
	t_imgdata img;

	img = data->img;
//	imgdrawbg(&img, 1024, 512, 0x0000FF00);
	imgdrawmap(&img, &data->map);
	raycast(data);
	moveplayer(data);
	imgdrawplayer(&img, data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, img.img, 0, 0);
}

void	imgdrawray(t_data *data, t_ray *r, int color)
{
	t_pos	a;
	t_pos	b;


	a.x = (int)data->player.x;
	a.y = (int)data->player.y;
	b.x = (int)r->x;
	b.y = (int)r->y;
	a.color = color;
	imgdrawline(a, b, data);
}

double	dist(t_player a, t_pos b)
{
	return(sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

double	horizontalcheck(t_data *data, t_ray *r, int dof)
{
	int		i;
	double	aTan;
	t_pos	m;
	
	aTan = -1 / tan(r->a);
	i = 0;
	while(i < 1)
	{
		dof = 0;
		if (r->a > M_PI)
		{
			r->y = (((int)data->player.y>>6)<<6) - 0.0001;
			r->x = (data->player.y - r->y) * aTan + data->player.x;
			r->yo = -64;
			r->xo = -r->yo * aTan;
		}
		if (r->a < M_PI)
		{
			r->y = (((int)data->player.y>>6)<<6) + 64;
			r->x = (data->player.y - r->y) * aTan + data->player.x;
			r->yo = 64;
			r->xo = -r->yo * aTan;
		}
		if (r->a == 0 || r->a == M_PI)
		{
			r->y = data->player.y;
			r->x = data->player.x;
			dof = 8;
		}
		while(dof < 8)
		{
			m.x = (int)(r->x)>>6;
			m.y = (int)(r->y)>>6;
			m.z = m.y * data->map.map_x + m.x;
			if (m.z > 0 && m.z < data->map.map_x * data->map.map_y && data->map.map[m.z] == 1)
				dof = 8;
			else
			{
				r->x += r->xo;
				r->y += r->yo;
				dof++;
			}
		}
		if(r->x >= 0 && r->x <= 1024 && r->y >= 0 && r->y <= 512)
			return (dist(data->player, m));
		i++;
	}
	return (-1);
}

double	verticalcheck(t_data *data, t_ray *r, int dof)
{
	int		i;
	double	nTan;
	t_pos	m;

	i = 0;
	nTan = -tan(r->a);
	while(i < 1)
	{
		printf("mz: %d my: %d, mapX: %d, mx: %d\n", m.z, m.y, data->map.map_x, m.x);
		dof = 0;
		if (r->a > M_PI / 2 && r->a < M_PI + M_PI / 2)
		{
			r->x = (((int)data->player.x>>6)<<6) - 0.0001;
			r->y = (data->player.x - r->x) * nTan + data->player.y;
			r->xo = -64;
			r->yo = -r->xo * nTan;
		}
		if (r->a < M_PI / 2 || r->a > M_PI + M_PI / 2)
		{
			r->x = (((int)data->player.x>>6)<<6) + 64;
			r->y = (data->player.x - r->x) * nTan + data->player.y;
			r->xo = 64;
			r->yo = -r->xo * nTan;
		}
		if (r->a == 0 || r->a == M_PI)
		{
			r->y = data->player.y;
			r->x = data->player.x;
			dof = 8;
		}
		while(dof < 8)
		{
			m.x = (int)(r->x)>>6;
			m.y = (int)(r->y)>>6;
			m.z = m.y * data->map.map_x + m.x;
			if (m.z > 0 && m.z < data->map.map_x * data->map.map_y && data->map.map[m.z] == 1)
				dof = 8;
			else
			{
				r->x += r->xo;
				r->y += r->yo;
				dof++;
			}
		}
		if(r->x >= 0 && r->x <= 1024 && r->y >= 0 && r->y <= 512)
			return(dist(data->player, m));
		i++;
	}
	return (-1);
}

void	raycast(t_data *data)
{
	t_ray	rh;
	t_ray	rv;
	t_pos	m;
	double	hdist;
	double	vdist;
	
	rh.a = data->player.a;
	rv.a = rh.a;
	hdist = horizontalcheck(data, &rh, 8);
	vdist = verticalcheck(data, &rv, 8);
	if ((hdist != -1 && hdist < vdist) || vdist == -1)
		imgdrawray(data, &rh, 0x00FF00);
	else if ((vdist != -1 && vdist < hdist) || hdist == -1)
		imgdrawray(data, &rv, 0xFF0000);
	
}

int main(void)
{
    t_data		data;
	t_player	player;
	t_imgdata	img;
	
	player.x = 72;
	player.y = 72;
	player.a = M_PI + M_PI / 2;
	data.player = player;
	arrayinit(&data);
	printf("x: %f | y: %f\n", data.player.x, data.player.y);
    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 1024, 512, "Hello world")) == NULL)
        return (EXIT_FAILURE);
//	mlx_key_hook(data.mlx_win, display_button, &data);
//	mlx_mouse_hook(data.mlx_win, display_button, &data);
	mlx_hook(data.mlx_win, 17, 1L<<17, exit_cub3d, &data);
//	mlx_hook(data.mlx_win, 2, 1L<<0, display_button, &data);				//show pressed buton
//	mlx_hook(data.mlx_win, 3, 1L<<1, display_buttonrelease, &data);			//show released button
	mlx_hook(data.mlx_win, 2, 1L<<0, key_hook, &data);
	mlx_hook(data.mlx_win, 3, 1L<<1, key_realease_hook, &data);
//	mlx_hook(data.mlx_win, 6, 1L<<6, display_button, &data);

	img.img = mlx_new_image(data.mlx_ptr, 1024, 512);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	data.img = img;
	data.map = mapinit(&data);
	displaymaparray(&data.map);
	printf("last: %d\n", data.map.map[61]);
	printf("mapS: %d, mapX: %d, mapY: %d\n", data.map.map_s, data.map.map_x, data.map.map_y);
//	printf("data.img.img: %p, img.img: %p\n", data.img.img, img.img);
//	imgdrawbg(&img, 1024, 512, 0x0000FF00);
	imgdrawmap(&img, &data.map);
	imgdrawplayer(&img, &data);
	raycast(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, img.img, 0, 0);
	mlx_loop_hook(data.mlx_ptr, render_next_frame, &data);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}