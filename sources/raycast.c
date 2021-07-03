/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 20:24:26 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/03 20:07:22 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	ray_dist(t_player *a, t_ray *b)
{
	return (sqrt((b->x - a->x) * (b->x - a->x)
			+ (b->y - a->y) * (b->y - a->y)));
}

double	dist(t_pos *a, int x, int y)
{
	return (sqrt((x - a->x) * (x - a->x) + (y - a->y) * (y - a->y)));
}

t_sprite	*sprite_struct_init(t_data *data, t_pos *pos, t_pos *mpos,
		double distance)
{
	t_sprite	*sprite;
	double		cosine;

	sprite = (t_sprite *)malloc(sizeof(t_sprite));
	if (sprite == NULL)
		return (NULL);
	sprite->pos = pos;
	sprite->angle = calculate_angle(data, pos->x, pos->y);
	cosine = cos(sprite->angle);
	if (cosine <= 0.55)
		cosine = 0.55;
	sprite->distance = distance * (cosine);
	sprite->next = NULL;
	sprite->draw_start_x = 0;
	sprite->draw_end_x = 0;
	sprite->draw_start_y = 0;
	sprite->draw_end_y = 0;
	sprite->sprite_screen_x = 0;
	sprite->tx = 0;
	sprite->txoffset = 0;
	sprite->ty = 0;
	sprite->tyoffset = 0;
	sprite->x = mpos->x;
	sprite->y = mpos->y;
	return (sprite);
}

static void	sorted_insert(t_sprite **head_ref, t_sprite *new_node)
{
	t_sprite	*current;

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

void	is_sprite(t_data *data, t_ray *ray, t_pos *m)
{
	t_pos		*newpos;
	t_sprite	*new_sprite;
	t_sprite	*current;
	double		distance;

	newpos = posstructinit();
	newpos->x = m->x * data->map->map_s + data->map->map_s / 2;
	newpos->y = m->y * data->map->map_s + data->map->map_s / 2 ;
	current = data->sprite_head;
	while (current != NULL)
	{
		if (current->x == m->x
			&& current->y == m->y)
		{
			free(newpos);
			return ;
		}
		current = current->next;
	}
	distance = dist(newpos, data->player->x, data->player->y);
	new_sprite = sprite_struct_init(data, newpos, m, distance);
	sorted_insert(&(data->sprite_head), new_sprite);
}

int	set_vertical_ray(t_data *data, t_ray *r)
{
	if (r->a > M_PI / 2 && r->a < M_PI + M_PI / 2)
	{
		r->x = (((int)data->player->x >> 6) << 6) - 0.0001;
		r->y = (data->player->x - r->x) * -tan(r->a) + data->player->y;
		r->xo = -64;
		r->yo = -r->xo * -tan(r->a);
	}
	if (r->a < M_PI / 2 || r->a > M_PI + M_PI / 2)
	{
		r->x = (((int)data->player->x >> 6) << 6) + 64;
		r->y = (data->player->x - r->x) * -tan(r->a) + data->player->y;
		r->xo = 64;
		r->yo = -r->xo * -tan(r->a);
	}
	if (r->a == M_PI / 2 || r->a == M_PI + M_PI / 2 )
		return (-1);
}

int	set_horizontal_ray(t_data *data, t_ray *r)
{
	if (r->a > M_PI)
	{
		r->y = (((int)data->player->y >> 6) << 6) - 0.0001;
		r->x = (data->player->y - r->y) * (-1 / tan(r->a)) + data->player->x;
		r->yo = -64;
		r->xo = -r->yo * (-1 / tan(r->a));
	}
	if (r->a < M_PI)
	{
		r->y = (((int)data->player->y >> 6) << 6) + 64;
		r->x = (data->player->y - r->y) * (-1 / tan(r->a)) + data->player->x;
		r->yo = 64;
		r->xo = -r->yo * (-1 / tan(r->a));
	}
	if (r->a == 0 || r->a == M_PI)
		return (-1);
}

void	search_hor_wall(t_data *data, t_ray *r, t_pos *m)
{
	while (m->y >= 0 && m->y < data->map->map_y && m->x >= 0 && m->x < data->map
		->map_x)
	{
		m->x = (int)(r->x) >> 6;
		m->y = (int)(r->y) >> 6;
		m->z = m->y * data->map->map_x + m->x;
		if (m->x >= data->map->map_x || m->y >= data->map->map_y || m->x < 0
			|| m->y < 0)
			break ;
		if (m->z > 0 && m->z < data->map->map_x * data->map->map_y && data->map
			->map[m->y][m->x] == 2)
			is_sprite(data, r, m);
		if (m->z > 0 && m->z < data->map->map_x * data->map->map_y && data->map
			->map[m->y][m->x] == 1)
			break ;
		else
		{
			r->x += r->xo;
			r->y += r->yo;
		}
	}
}

double	horizontalcheck(t_data *data, t_ray *r)
{
	t_pos	*m;

	m = posstructinit();
	if (!set_horizontal_ray(data, r))
		return (-1);
	search_hor_wall(data, r, m);
	free(m);
	if (r->x > 0 && r->y > 0)
		return (ray_dist(data->player, r));
	return (-1);
}

void	search_vert_walls(t_data *data, t_ray *r, t_pos *m)
{
	while (m->y >= 0 && m->y < data->map->map_y && m->x >= 0 && m->x < data
		->map->map_x)
	{
		m->x = (int)(r->x) >> 6;
		m->y = (int)(r->y) >> 6;
		m->z = m->y * data->map->map_x + m->x;
		if (m->x >= data->map->map_x || m->y >= data->map->map_y || m->x < 0
			|| m->y < 0)
			break ;
		if (m->z > 0 && m->z < data->map->map_x * data->map->map_y && data
			->map->map[m->y][m->x] == 2)
			is_sprite(data, r, m);
		if (m->z > 0 && m->z < data->map->map_x * data->map->map_y && data
			->map->map[m->y][m->x] == 1)
			break ;
		else
		{
			r->x += r->xo;
			r->y += r->yo;
		}
	}
}

double	verticalcheck(t_data *data, t_ray *r)
{
	t_pos	*m;

	m = posstructinit();
	if (!set_vertical_ray(data, r))
		return (-1);
	search_vert_walls(data, r, m);
	free(m);
	if (r->x >= 0 && r->y >= 0)
		return (ray_dist(data->player, r));
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
	if (y < 0)
		angle = -acos(cos);
	if (y >= 0)
		angle = acos(cos);
	angle = angle - data->player->a;
	if (angle <= M_PI + M_PI / 3)
		angle += 2 * M_PI;
	if (angle >= M_PI + M_PI / 3)
		angle -= 2 * M_PI;
	return (angle);
}

t_posf	*posfstructinit(void)
{
	t_posf	*p;

	p = (t_posf *)malloc(sizeof (t_posf));
	if (p == NULL)
		return (NULL);
	p->color = 0;
	p->x = 0;
	p->y = 0;
	p->z = 0;
	return (p);
}

int	get_screen_x(t_data *data, t_sprite *sprite)
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
	i = data->win_w / 2;
	dr = (80 / (double)data->win_w);
	i += angle / dr;
	return (i);
}

void	project_sprite(t_data *data, t_sprite *sprite, double lineH)
{
	sprite->sprite_screen_x = get_screen_x(data, sprite);
	sprite->draw_start_x = sprite->sprite_screen_x - lineH / 2;
	sprite->draw_end_x = sprite->draw_start_x + lineH;
	if (lineH > data->win_h)
		lineH = data->win_h;
	if (sprite->draw_end_x > data->win_w)
		sprite->draw_end_x = data->win_w;
	sprite->draw_start_y = (data->win_h / 2) - (lineH / 2);
	sprite->draw_end_y = sprite->draw_start_y + lineH;
}

void	put_sprite_setup(t_data *data, t_sprite *s, double lineH)
{
	if (lineH > data->win_h)
		s->tyoffset = (lineH - data->win_h) / 2;
	if (s->draw_start_x < 0)
	{
		s->txoffset = - (s->draw_start_x);
		s->draw_start_x = 0;
	}
}

static void	draw(t_data *data, t_sprite *s, int i, int j)
{
	char	*src;

	src = data->sp_texture->addr + (int)s->ty * data->sp_texture
		->line_len + (int)s->tx * (data->sp_texture->bpp / 8);
	if (*(unsigned int *)src != 0xFF000000)
		*(unsigned int *)(data->img->addr + (j * data->img->line_len
					+ i * (data->img->bpp / 8))) = *(unsigned int *)src;
}

void	put_sprite(t_data *data, t_sprite *s, t_raydist *rdist,
		double lineH)
{
	float	step;
	char	*src;
	int		i;
	int		j;

	step = data->sp_texture->height / lineH;
	put_sprite_setup(data, s, lineH);
	i = s->draw_start_x;
	s->tx = s->txoffset * step;
	while (i < s->draw_end_x)
	{
		j = s->draw_start_y;
		s->ty = s->tyoffset * step;
		while (j < s->draw_end_y && s->distance < rdist->td[i])
		{
			draw(data, s, i, j);
			s->ty += step;
			j++;
		}
		s->tx += step;
		i++;
	}
}

void	free_sprites(t_sprite **head_ref)
{
	t_sprite	*current;
	t_sprite	*next;

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
		lineH = (data->map->map_s * data->win_h) / current->distance;
		project_sprite(data, current, lineH);
		put_sprite(data, current, rdist, lineH);
		current = current->next;
	}
	free_sprites(&data->sprite_head);
}

t_ray	*ray_struct_init(void)
{
	t_ray	*r;

	r = (t_ray *)malloc(sizeof(t_ray));
	if (r == NULL)
		return (NULL);
	r->a = 0;
	r->x = 0;
	r->xo = 0;
	r->y = 0;
	r->yo = 0;
	return (r);
}

t_rays	*rays_struct_init(void)
{
	t_rays	*r;

	r = (t_rays *)malloc(sizeof(t_rays));
	if (r == NULL)
		return (NULL);
	r->h = ray_struct_init();
	r->p = posstructinit();
	r->t = ray_struct_init();
	r->texture = imgstructinit();
	r->v = ray_struct_init();
	return (r);
}

double	totalcheck(t_data *data, t_raydist rdist, t_rays *r)
{
	double	td;

	if ((rdist.hd != -1 && rdist.hd < rdist.vd) || rdist.vd == -1)
	{
		if (r->h->a >= 0 && r->h->a < M_PI)
			r->texture = data->no_texture;
		else
			r->texture = data->so_texture;
		td = rdist.hd;
		r->t = r->h;
	}
	else if ((rdist.vd != -1 && rdist.vd < rdist.hd) || rdist.hd == -1)
	{
		if (r->h->a >= M_PI / 2 && r->h->a < M_PI + (M_PI / 2))
			r->texture = data->we_texture;
		else
			r->texture = data->ea_texture;
		td = rdist.vd;
		r->t = r->v;
	}
	return (td);
}

double	limit_angle(double a)
{
	if (a < 0)
		a += 2 * M_PI;
	if (a > 2 * M_PI)
		a -= 2 * M_PI;
	return (a);
}

void	raycast(t_data *data)
{
	int			i;
	float		ca;
	double		dr;
	t_rays		*r;
	t_raydist	rdist;

	r = rays_struct_init();
	rdist.td = (double *)malloc(sizeof(double) * data->win_w);
	i = 0;
	dr = (80 / (double)data->win_w) * DR;
	while (i < data->win_w)
	{
		r->h->a = data->player->a - dr * ((data->win_w / 2) - i);
		r->h->a = limit_angle(r->h->a);
		r->v->a = r->h->a;
		rdist.hd = horizontalcheck(data, r->h);
		rdist.vd = verticalcheck(data, r->v);
		rdist.td[i] = totalcheck(data, rdist, r);
		ca = data->player->a - r->h->a;
		ca = limit_angle(ca);
		rdist.td[i] = rdist.td[i] * cos(ca);
		draw_walls(data, rdist, i, r->texture, r->t);
		i++;
	}
	draw_sprites(data, &rdist);
}
