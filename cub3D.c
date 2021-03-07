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


int	parser(char *)
int	main(int argc, char **argv)
{
	int		fd;
	data_t	data;

	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		printf("error in open\n");
		return (-1);
	}
	if ((data.mlx = mlx_init()) == NULL)
		return (-1);
	if ((data.win = mlx_new_window (data.mlx, 100, 100, "cub3d")) == NULL)
		return (-1);
	mlx_loop(data.mlx);
	return (1);
}