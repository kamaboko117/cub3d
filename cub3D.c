#include "libft/libft.h"
#include <mlx.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct	data_s
{
    void          *mlx;
    void          *win;
}				data_t;

typedef struct	settings_s
{
	int	xres;
	int	yres;
}				settings_t;

typedef struct	player_s
{
	int	x;
	int	y;
}				player_t;

settings_t	parser(int fd)
{
	settings_t	settings;
	char	*line;
	char	*info;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		printf("%s\n", line);
		if ((info = ft_strchr(line, 'R')) && line[1] == ' ')
		{
			settings.xres = ft_atoi(info + 2);
			settings.yres = ft_atoi(info + 2 + ft_numlen(settings.xres, 10) + 1);
			return(settings);
		}
	}
	printf("%s\n", line);
	if ((info = ft_strchr(line, 'R')) && line[1] == ' ')
	{
		settings.xres = ft_atoi(info + 2);
		settings.yres = ft_atoi(info + 2 + ft_numlen(settings.xres, 10) + 1);
		return(settings);
	}
	settings.xres = 0;
	settings.yres = 0;
	return(settings);
}

int	main(int argc, char **argv)
{
	int			fd;
	data_t		data;
	settings_t	settings;
	player_t	player;

	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		printf("error in open\n");
		return (-1);
	}
	settings = parser(fd);
	if (settings.xres == 0 || settings.yres == 0)
	{
		printf("x: %d y: %d\n", settings.xres, settings.yres);
		return (-1);
	}
	if ((data.mlx = mlx_init()) == NULL)
		return (-1);
	if ((data.win = mlx_new_window (data.mlx, settings.xres, settings.yres, "cub3d")) == NULL)
		return (-1);
	mlx_loop(data.mlx);
	return (1);
}