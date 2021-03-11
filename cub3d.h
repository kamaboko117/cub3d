#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdio.h>
# define DR 0.0174533

typedef struct	s_line
{
    int	error;
    int	offset;
    int	sign_y;
    int	sign_x;
    int	delta_y;
    int	delta_x;
}                t_line;
typedef struct	s_pos
{
    int	y;
    int	x;
    int	z;
    int	color;
}                t_pos;
typedef struct	player_s
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	dxleft;
	double	dyleft;
	double	a;
}				player_t;
typedef struct	map_s
{
	int	map_x;
	int	map_y;
	int	map_s;
	int map[64];
}				map_t;
typedef struct	imgdata_s
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				imgdata_t;
typedef struct	s_ray
{
	double	x;
	double	y;
	double	a;
	double	xo;
	double	yo;	
}				t_ray;
typedef struct	s_raydist
{
	double	hdist;
	double	vdist;
	double	tdist;
}				t_raydist;
typedef struct	data_s
{
    void		*mlx_ptr;
    void		*mlx_win;
	char		inputs[10];
	player_t	player;
	imgdata_t	img;
	map_t		map;
}                 data_t;

void	moveplayer(data_t *data);
void	forward(player_t *player, int velocity);
void	backward(player_t *player, int velocity);
void	lookleft(player_t *player, double sensitivity);
void	lookright(player_t *player, double sensitivity);
int		key_hook(int keycode, data_t *data);
int 	display_keycode(int keycode, data_t *data);
int 	display_button(int button, int x, int y, data_t *data);
void	imgdrawline(t_pos a, t_pos b, data_t *data);
int		exit_cub3d(data_t *data);
void	imgputpixel(imgdata_t *img, int x, int y, int color);
void	imgputsquare(imgdata_t *img, int size, int x, int y, int color);
void	imgdrawbg(imgdata_t *img, int xres, int yres, int color);
void	displaymaparray(map_t *map);
void	imgdrawmap(imgdata_t *img, map_t *map);
void	imgdrawplayer(imgdata_t *img, data_t *data);
int		render_next_frame(data_t *data);
map_t	mapinit(data_t *data);
void	arrayinit(data_t *data);
void	raycast(data_t *data);
#endif