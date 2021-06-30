#include "../cub3d.h"

double	ray_dist(t_player *a, t_ray *b)
{
	return(sqrt((b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y)));
}

double	dist(t_pos *a, int x, int y)
{
	return(sqrt((x - a->x) * (x - a->x) + (y - a->y) * (y - a->y)));
}

t_sprite	*sprite_struct_init(t_data *data, t_pos *pos, t_pos *mpos, double distance, int screenx)
{
	t_sprite	*sprite;
	double		cosinus;

	if (!(sprite = (t_sprite *)malloc(sizeof(t_sprite))))
		return (NULL);
	sprite->pos = pos;
	sprite->angle = calculate_angle(data, pos->x, pos->y);
	cosinus = cos(sprite->angle);
	if (cosinus <= 0.55)
		cosinus = 0.55;
	sprite->distance = distance * (cosinus);
	sprite->next = NULL;
	sprite->draw_start_x = 0;
	sprite->draw_end_x = 0;
	sprite->draw_start_y = 0;
	sprite->draw_end_y = 0;
	sprite->sprite_x = 0;
	sprite->sprite_y = 0;
	sprite->sprite_screen_x = screenx;
	sprite->sprite_height = 0;
	sprite->sprite_width = 0;
	sprite->x = mpos->x;
	sprite->y = mpos->y;
	sprite->text_x = 0;
	sprite->text_y = 0;
	return (sprite);
}

static void	sorted_insert(t_sprite **head_ref, t_sprite *new_node)
{
	t_sprite *current;

	if ((*head_ref) == NULL || (*head_ref)->distance <= new_node->distance)
	{
		new_node->next = (*head_ref);
		(*head_ref) = new_node;
	}
	else
	{
		current = (*head_ref);
		while (current->next != NULL
			&& current->next->distance >= new_node->distance)
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}

void		is_sprite(t_data *data, t_ray *ray, int i, t_pos *m)
{
	t_pos		*newpos;
	t_sprite	*new_sprite;
	t_sprite	*current;
	double		distance;

	if (!(newpos = (t_pos *)malloc(sizeof(t_pos))))
		return ;
	newpos->x = m->x * data->map->map_s + data->map->map_s / 2;
	newpos->y = m->y * data->map->map_s + data->map->map_s / 2 ;
	current = data->sprite_head;
	while (current != NULL)
	{
		if (current->x == m->x
			&& current->y == m->y)
		{
			free(newpos); //should be enough since no posinit needed (?)
			return ;
		}
		current = current->next;
	}
	distance = sqrt((newpos->x - data->player->x) * (newpos->x - data->player->x) + (newpos->y - data->player->y) * (newpos->y - data->player->y));
//	printf("current distance: %f, newpos x: %d, newpos y: %d, player x: %f, player y: %f\n", distance, newpos->x, newpos->y, data->player->x, data->player->y);
	new_sprite = sprite_struct_init(data, newpos, m, distance, i);
	sorted_insert(&(data->sprite_head), new_sprite);
}

double	horizontalcheck(t_data *data, t_ray *r, int screenx, int dof)
{
	double	aTan;
	t_pos	*m;
	
	m = posstructinit();
	aTan = -1 / tan(r->a);
	dof = 0;
	if (r->a > M_PI)
	{
		r->y = (((int)data->player->y>>6)<<6) - 0.0001;
		r->x = (data->player->y - r->y) * aTan + data->player->x;
		r->yo = -64;
		r->xo = -r->yo * aTan;
	}
	if (r->a < M_PI)
	{
		r->y = (((int)data->player->y>>6)<<6) + 64;
		r->x = (data->player->y - r->y) * aTan + data->player->x;
		r->yo = 64;
		r->xo = -r->yo * aTan;
	}
	if (r->a == 0 || r->a == M_PI)
		return (-1);
	while(dof < 8 && m->y >= 0 && m->y < data->map->map_y && m->x >= 0 && m->x < data->map->map_x)
	{
		m->x = (int)(r->x)>>6;
		m->y = (int)(r->y)>>6;
		m->z = m->y * data->map->map_x + m->x;
		if (m->x >= data->map->map_x || m->y >= data->map->map_y || m->x < 0 || m->y < 0)
			break;
//	printf("mx: %d mapx: %d my: %d mapy: %d\n", m->x, data->map->map_x, m->y, data->map->map_y);
		if (m->z > 0 && m->z < data->map->map_x * data->map->map_y && data->map->map[m->y][m->x] == 2) //if a sprite is found
		{
			is_sprite(data, r, screenx, m);
		}
		if (m->z > 0 && m->z < data->map->map_x * data->map->map_y && data->map->map[m->y][m->x] == 1)
			break;
		else
		{
			r->x += r->xo;
			r->y += r->yo;
		}
	}
	//	printf("H: mz: %d my: %d, mapX: %d, mx: %d\n", m->z, m->y, data->map->map_x, m->x);
	free(m);
	if(r->x > 0 && r->y > 0)
		return (ray_dist(data->player, r));
	return (-1);
}

double	verticalcheck(t_data *data, t_ray *r, int screenx, int dof)
{
	double	nTan;
	t_pos	*m;

	m = posstructinit();
	nTan = -tan(r->a);
	dof = 0;
	if (r->a > M_PI / 2 && r->a < M_PI + M_PI / 2)
	{
		r->x = (((int)data->player->x>>6)<<6) - 0.0001;
		r->y = (data->player->x - r->x) * nTan + data->player->y;
		r->xo = -64;
		r->yo = -r->xo * nTan;
	}
	if (r->a < M_PI / 2 || r->a > M_PI + M_PI / 2)
	{
		r->x = (((int)data->player->x>>6)<<6) + 64;
		r->y = (data->player->x - r->x) * nTan + data->player->y;
		r->xo = 64;
		r->yo = -r->xo * nTan;
	}
	if (r->a == M_PI / 2 || r->a == M_PI + M_PI / 2 )
		return (-1);
	while(dof < 8 && m->y >= 0 && m->y < data->map->map_y && m->x >= 0 && m->x < data->map->map_x)
	{
		m->x = (int)(r->x)>>6;
		m->y = (int)(r->y)>>6;
		m->z = m->y * data->map->map_x + m->x;
		if (m->x >= data->map->map_x || m->y >= data->map->map_y || m->x < 0 || m->y < 0)
			break;
		if (m->z > 0 && m->z < data->map->map_x * data->map->map_y && data->map->map[m->y][m->x] == 2) //if a sprite is found
		{
			is_sprite(data, r, screenx, m);
		} 
		if (m->z > 0 && m->z < data->map->map_x * data->map->map_y && data->map->map[m->y][m->x] == 1)
			break;
		else
		{
			r->x += r->xo;
			r->y += r->yo;
		}
	}
//	printf("V: mz: %d my: %d, mapX: %d, mx: %d\n", m->z, m->y, data->map->map_x, m->x);
//	printf("%f\n", r->x);
	free(m);
	if(r->x >= 0 && r->y >= 0)
		return(ray_dist(data->player, r));
	return (-1);
}

float	calculate_angle(t_data *data, int x, int y)
{
	float	hypotenuse;
	float	angle;
	t_pos	*origin;
	float	cos;

	origin = posstructinit();
	x -= data->player->x;
	y -= data->player->y;
	hypotenuse = dist(origin, x, y);
	cos = (x) / hypotenuse;
//	printf("px: %f, playerx: %f, py: %f\n", p->x, data->player->x, p->y);
	if(x < 0)
	{
		if(y < 0)
		{
			angle = -acos(cos);
		}
		if (y > 0)
		{
			angle = acos(cos);
		}
		if (y == 0)
			angle = M_PI;
	}
	if(x > 0)
	{
		if (y == 0)
			angle = 0;
		if (y < 0)
		{
			angle = -acos(cos);
		}
		if(y > 0)
		{
			angle =acos(cos);
		}
	}
	if(x == 0)
	{
		if (y > 0)
			angle = M_PI / 2;
		else
			angle = M_PI + M_PI / 2;
	}
	angle = angle - data->player->a;
	if (angle <= M_PI + M_PI / 3)
		angle += 2 * M_PI;
	if (angle >= M_PI + M_PI / 3)
		angle -= 2 * M_PI;
	return (angle);
}

t_posf	*posfstructinit()
{
	t_posf	*p;

	if (!(p = (t_posf *)malloc(sizeof (t_posf))))
		return (NULL);
	p->color = 0;
	p->x = 0;
	p->y = 0;
	p->z = 0;
	return (p);
}

int		get_screen_x(t_data *data, t_sprite *sprite)
{
	int		i;
	t_pos	p;
	float	angle;
	double	dr;

	p = *posstructinit();
	p.x = sprite->pos->x;
	p.y = sprite->pos->y;
	angle = sprite->angle;
	angle = angle / DR;
	i = data->win_width / 2;
	dr = (80 / (double)data->win_width);
	i += angle / dr;
	return (i);
	
}

void	project_sprite(t_data *data, t_sprite *sprite, double lineH)
{
	sprite->sprite_screen_x = get_screen_x(data, sprite);
	sprite->draw_start_x = sprite->sprite_screen_x - lineH / 2;
	sprite->draw_end_x = sprite->draw_start_x + lineH;
	if (lineH > data->win_height)
		lineH = data->win_height;
	if (sprite->draw_end_x > data->win_width)
		sprite->draw_end_x = data->win_width;
	sprite->draw_start_y = (data->win_height / 2) - (lineH / 2); 
	sprite->draw_end_y = sprite->draw_start_y + lineH;
}

void	put_sprite(t_data *data, t_sprite *sprite, t_raydist *rdist, double lineH)
{
	float	step;
	float	xstep;
	float	tyoffset;
	float	ty;
	float	tx;
	float	txoffset;
	char	*src;
	int		i;
	int		j;

//	printf("sp line length: %d\n", data->sp_texture->line_length);
	step = data->sp_texture->height / lineH;
	xstep = data->sp_texture->width / lineH;
	tyoffset = 0;
	txoffset = 0;
	if (lineH > data->win_height)
	{
		tyoffset = (lineH - data->win_height) / 2;
	}
	if (sprite->draw_start_x < 0)
	{
		
		txoffset = - (sprite->draw_start_x);
		sprite->draw_start_x = 0;
		printf("txoffset: %f\n", txoffset);
	}
	i = sprite->draw_start_x;
//	ty = tyoffset * step;
	tx = txoffset * step;
	while (i < sprite->draw_end_x)
	{
		j = sprite->draw_start_y;
		ty = tyoffset * step;
	//	printf("j: %d, draw end y: %d, i: %d, draw end x: %d, sprite distance: %f, rdist: %f, sprite texture: %s\n", j, sprite->draw_end_y, i, sprite->draw_end_x, sprite->distance, rdist->tdist[i], data->sp_texture->path);
		while (j < sprite->draw_end_y && sprite->distance < rdist->tdist[i]) 
		{
			//printf("src: %s, ty: %d\n", src, (int)ty);
			src = data->sp_texture->addr + (int)ty * data->sp_texture->line_length + (int)tx * (data->sp_texture->bits_per_pixel / 8);
			if (*(unsigned int*)src != 0xFF000000)
				*(unsigned int*)(data->img->addr + (j * data->img->line_length + i * (data->img->bits_per_pixel / 8))) = *(unsigned int*)src;
			ty += step; 
			j++;
		}
		tx += step;
		i++;
	}
}

void	free_sprites(t_sprite **head_ref)
{
	t_sprite *current;
	t_sprite *next;

	current = (*head_ref);
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	(*head_ref) = NULL;
}

void	draw_sprites(t_data *data, t_raydist *rdist)
{
	t_sprite	*current;
	double		lineH;

	current = data->sprite_head;
	while (current != NULL)
	{
		lineH = (data->map->map_s * data->win_height) / current->distance;
		//printf("lineH: %f, distance: %f, sprite pos: %d %d\n", lineH, current->distance, current->pos->x, current->pos->y);
		project_sprite(data, current, lineH);
		put_sprite(data, current, rdist, lineH);
		current = current->next;
	}
	free_sprites(&data->sprite_head);
}

void	raycast(t_data *data)
{
	int i;
	float	ca;
	int color;
	double dr;
	t_imgdata	*texture;
	t_ray	rh;
	t_ray	rv;
	t_ray	rt;
	t_pos	m;
	t_raydist	rdist;
	
	rdist.tdist = (double *)malloc(sizeof(double) * data->win_width); // will have to init this and sset values to 0 instead
	i= 0;
	dr = (80 / (double)data->win_width) * DR;
	while (i < data->win_width)
	{
		rh.a = data->player->a - dr * ((data->win_width / 2) - i);
		if (rh.a < 0)
			rh.a += 2 * M_PI;
		if (rh.a > 2 * M_PI)
			rh.a -= 2 * M_PI;
		rv.a = rh.a;
		rdist.hdist = horizontalcheck(data, &rh, i, 8);
		rdist.vdist = verticalcheck(data, &rv, i, 8);
		if ((rdist.hdist != -1 && rdist.hdist < rdist.vdist) || rdist.vdist == -1)
		{
			//imgdrawray(data, &rh, 0x00FF00);
			if (rh.a >= 0 && rh.a < M_PI)
				texture = data->no_texture;
			else
				texture = data->so_texture;
			rdist.tdist[i] = rdist.hdist;
			rt = rh;
			color = 0x00FF00;
		}
		else if ((rdist.vdist != -1 && rdist.vdist < rdist.hdist) || rdist.hdist == -1)
		{
			//imgdrawray(data, &rv, 0xFF0000);
			if (rh.a >= M_PI / 2 && rh.a < M_PI + (M_PI / 2))
				texture = data->we_texture;
			else
				texture = data->ea_texture;
			rdist.tdist[i] = rdist.vdist;
			rt = rv;
			color = 0xFF0000;
		}
		ca = data->player->a - rh.a;
		if (ca < 0)
			ca += 2 * M_PI;
		if (ca > 2 * M_PI)
			ca -= 2 * M_PI;
		rdist.tdist[i] = rdist.tdist[i] * cos(ca);
		draw_walls(data, rdist, i, texture, &rt);
		i++;
	}
	draw_sprites(data, &rdist);
}
