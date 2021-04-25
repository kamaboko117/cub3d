#include "../cub3d.h"

void	imgputpixel(t_imgdata *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	imgputsquare(t_imgdata *img, int size, int x, int y, int color)
{
	int	len;
	int wid;

//	printf("x: %d, y: %d\n", x, y);
	wid = size;
	while (wid)
	{
		len = size;
		while (len)
		{
			imgputpixel(img, x + len, y + wid, color);
			len--;
		}
		wid--;
	}
}

void	imgdrawbg(t_imgdata *img, int xres, int yres, int color)
{
	int	i;
	
	while(xres)
	{
		i = yres;
		while(i)
		{
			imgputpixel(img, xres, i, color);
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
	while(map->map[y])
	{
		x = 0;
		while(map->map[y][x])
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
	imgputsquare(img, 8, data->player->x - 4, data->player->y - 4, 0x00FF0000);
	imgdrawline(start, end, data);
}
