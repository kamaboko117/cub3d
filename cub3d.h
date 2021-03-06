/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:05:51 by asaboure          #+#    #+#             */
/*   Updated: 2021/09/24 14:19:12 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define DR 0.0174533

typedef struct s_line
{
	int	error;
	int	offset;
	int	sign_y;
	int	sign_x;
	int	delta_y;
	int	delta_x;
}				t_line;
typedef struct s_pos
{
	int	y;
	int	x;
	int	z;
	int	color;
}				t_pos;
typedef struct s_posf
{
	double	y;
	double	x;
	double	z;
	int		color;
}				t_posf;
typedef struct s_player
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
typedef struct s_map
{
	int		map_x;
	int		map_y;
	int		map_s;
	int		**map;
	char	*tmpmap;
}				t_map;
typedef struct s_imgdata
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	char	*path;
}				t_imgdata;
typedef struct s_ray
{
	double		x;
	double		y;
	double		a;
	double		xo;
	double		yo;
	t_imgdata	*txt;
	float		step;
	float		toffset;
}				t_ray;
typedef struct s_rays
{
	t_ray		h;
	t_ray		v;
	t_ray		t;
	t_pos		*p;
	t_imgdata	*texture;
}				t_rays;
typedef struct s_raydist
{
	double	hd;
	double	vd;
	double	*td;
}				t_raydist;
typedef struct s_inputs
{
	char	w;
	char	a;
	char	s;
	char	d;
	char	left;
	char	right;
}				t_inputs;
typedef struct s_sprite
{
	t_pos				*pos;
	double				distance;
	int					draw_start_x;
	int					draw_end_x;
	int					draw_start_y;
	int					draw_end_y;
	int					sprite_screen_x;
	int					x;
	int					y;
	double				angle;
	double				tyoffset;
	double				txoffset;
	double				ty;
	double				tx;
	struct s_sprite		*next;
}				t_sprite;
typedef struct s_data
{
	int			win_h;
	int			win_w;
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
	t_sprite	*sprite_head;
	t_map		*map;
}				t_data;

void		moveplayer(t_data *data);
void		forward(t_player *player, int velocity, t_data *data);
void		backward(t_player *player, int velocity, t_data *data);
void		lookleft(t_player *player, double sensitivity);
void		lookright(t_player *player, double sensitivity);
int			key_hook(int keycode, t_data *data);
int			display_keycode(int keycode);
int			display_button(int button, int x, int y);
void		imgdrawline(t_pos a, t_pos b, t_data *data);
int			exit_cub3d(t_data *data);
void		imgputpixel(t_imgdata *img, int x, int y, int color);
void		imgputsquare(t_imgdata *img, int size, t_pos *p, int color);
void		imgdrawbg(t_imgdata *img, int xres, int yres, t_data *data);
void		displaymaparray(t_map *map);
void		imgdrawmap(t_data *data, t_imgdata *img, t_map *map);
void		imgdrawplayer(t_imgdata *img, t_data *data);
int			render_next_frame(t_data *data);
void		raycast(t_data *data);
void		clear_game(t_data *data);
int			isempty(char *line);
int			isrow(char *row);
int			isdirection(char c);
void		get_resolution(char *line, int *width, int *height);
void		free_split(char **str);
void		get_color(char *line, int *color, t_data *data);
int			get_color_handle(char **rgb, t_data *data);
void		exit_failure(char *error, t_data *data);
void		read_cub(char *cub_path, t_data *data);
t_data		*datainit(void);
void		puterror(char *str);
int			isempty(char *line);
int			isdirection(char c);
int			isrow(char *row);
void		init_player(t_data *data);
void		check_cub_data(t_data *data);
void		get_layout(t_data *data);
void		check_layout(t_data *data, t_map *map, t_player *player);
void		set_position(t_player *player, float pos_x, float pos_y);
void		clear_image(t_imgdata *img, void *mlx);
void		game_loop(t_data *data);
t_map		*mapstructinit(void);
void		draw_walls(t_data *data, t_raydist *rdist, int r, t_ray *ray);
t_pos		*posstructinit(t_data *data);
void		imgdrawray(t_data *data, t_ray *r, int color);
t_imgdata	*imgstructinit(t_data *data);
float		calculate_angle(t_data *data, int x, int y);
void		get_texture(t_data *data);
double		dist(t_pos *a, int x, int y);
double		ray_dist(t_player *a, t_ray *b);
t_sprite	*sprite_struct_init(t_data *data, t_pos *pos, t_pos *mpos,
				double distance);
t_rays		rays_struct_init(t_data *data);
void		free_sprites(t_sprite **head_ref);
double		limit_angle(double a);
int			get_screen_x(t_data *data, t_sprite *sprite);
void		put_sprites(t_data *data, t_raydist *rdist);
void		is_sprite(t_data *data, t_pos *m);
void		search_vert_walls(t_data *data, t_ray *r, t_pos *m);
int			set_vertical_ray(t_data *data, t_ray *r);
int			set_horizontal_ray(t_data *data, t_ray *r);
void		search_hor_wall(t_data *data, t_ray *r, t_pos *m);
int			checkcollision(double x, double y, t_data *data);
t_pos		*tpos_set(t_data *data, int x, int y, int color);
t_raydist	rdist_struct_init(t_data *data);
void		rays_init(t_data *data, double dr, int i, t_rays *r);
void		check_color(t_data *data, int color);
#endif