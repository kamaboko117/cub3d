#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
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
	char	dir;
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	dxleft;
	double	dyleft;
	double	a;
}				t_player;
typedef struct	map_s
{
	int		map_x;
	int		map_y;
	int		map_s;
	int		**map;
	char	*tmpmap;
}				map_t;
typedef struct	imgdata_s
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	char	*path;
}				t_imgdata;
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
typedef	struct	s_inputs
{
	char	w;
	char	a;
	char	s;
	char	d;
	char	left;
	char	right;
}				t_inputs;
typedef struct	data_s
{
	int			win_height;
	int			win_width;
    void		*mlx_ptr;
    void		*mlx_win;
	int			map_started;
	int			map_stopped;
	int			save;
	int			c_color;
	int			f_color;
	t_inputs	*inputs;
	t_player	*player;
	t_imgdata	*img;
	t_imgdata	*no_texture;
	t_imgdata	*ea_texture;
	t_imgdata	*so_texture;
	t_imgdata	*we_texture;
	t_imgdata	*sp_texture;
	map_t		*map;
}                 t_data;

void	moveplayer(t_data *data);
void	forward(t_player *player, int velocity, t_data *data);
void	backward(t_player *player, int velocity, t_data *data);
void	lookleft(t_player *player, double sensitivity);
void	lookright(t_player *player, double sensitivity);
int		key_hook(int keycode, t_data *data);
int 	display_keycode(int keycode, t_data *data);
int 	display_button(int button, int x, int y, t_data *data);
void	imgdrawline(t_pos a, t_pos b, t_data *data);
int		exit_cub3d(t_data *data);
void	imgputpixel(t_imgdata *img, int x, int y, int color);
void	imgputsquare(t_imgdata *img, int size, int x, int y, int color);
void	imgdrawbg(t_imgdata *img, int xres, int yres, t_data *data);
void	displaymaparray(map_t *map);
void	imgdrawmap(t_imgdata *img, map_t *map);
void	imgdrawplayer(t_imgdata *img, t_data *data);
int		render_next_frame(t_data *data);
void	raycast(t_data *data);
void	clear_game(t_data *data);
int		isempty(char *line);
int		isrow(char *row);
int		isdirection(char c);
void	get_resolution(char *line, int *width, int *height);
void	free_split(char **str);
void	get_color(char *line, int *color, t_data *data);
int		get_color_handle(char **rgb, t_data *data);
void	exit_failure(char *error, t_data *data);
void	read_cub(char *cub_path, t_data *data);
t_data	*datainit();
void	puterror(char *str);
int		isempty(char *line);
int		isdirection(char c);
int		isrow(char *row);
void	init_player(t_data *data);
void	check_cub_data(t_data *data);
void	get_layout(t_data *data);
void	check_layout(t_data *data, map_t *map, t_player *player);
void	set_position(t_player *player, float pos_x, float pos_y);
void	clear_image(t_imgdata *img, void *win, void *mlx);
void	game_loop(t_data *data);
map_t	*mapstructinit();
void	draw_walls(t_data *data, t_raydist rdist, int r, t_imgdata *texture, t_ray *ray);
t_pos	*posstructinit();
#endif