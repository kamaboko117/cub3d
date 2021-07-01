#include "../../cub3d.h"

void	imgputpixel(t_imgdata *img, int x, int y, int color)
{
	char	*dst;

//	printf("%d x %d\n", img->width, img->height);
	if (x < 0 || x > img->width || y < 0 || y > img->height)
		return;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void	imgputsquare(t_imgdata *img, int size, int x, int y, int color)
{
	int	len;
	int wid;

//	printf("x: %d, y: %d\n", x, y);
	wid = size - 1;
	while (wid >= 0)
	{
		len = size - 1;
		while (len >= 0)
		{
			imgputpixel(img, x + len, y + wid, color);
			len--;
		}
		wid--;
	}
}

void	imgdrawbg(t_imgdata *img, int xres, int yres, t_data *data)
{
	int	i;
	
	while(xres >= 0)
	{
		i = yres;
		while(i >= 0)
		{
			if(i < yres / 2)
				imgputpixel(img, xres, i, data->c_color);
			if(i >= yres / 2)
				imgputpixel(img, xres, i, data->f_color);
			i--;
		}
		xres--;
	}
}

void	imgdrawmap(t_imgdata *img, map_t *map)
{
	int	y;
	int x;
	int	color;

	y = 0;
//	printf("%i\n", map->map_y);
	while(y < map->map_y)
	{
		x = 0;
		while(x < map->map_x)
		{
			color = 0x002C2F33;
			if (map->map[y][x] == 1)
				color = 0x007289DA;
			imgputsquare(img, map->map_s, x * map->map_s, y * map->map_s, color);
			x++;			
		}
		y++;
	}
}

void	imgdrawplayer(t_imgdata *img, t_data *data)
{
	t_pos	start;
	t_pos	end;

	start.color = 0xFFFF00;
	start.x = data->player->x;
	start.y = data->player->y;
	end.x = start.x + 10 * cos(data->player->a);
	end.y = start.y + 10 * sin(data->player->a);
	
//	printf("%f\n", data->player.a);
//	printf("start: %d, %d | end: %d, %d\n", start.x, start.y, end.x, end.y);
	imgputsquare(img, 8, data->player->x - 3, data->player->y - 3, 0x00FF0000);
	imgdrawline(start, end, data);
}
