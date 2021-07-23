/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 20:24:26 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/23 18:06:39 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

double	totalcheck(t_data *data, t_raydist *rdist, t_rays *r)
{
	double	td;

	if ((rdist->hd != -1 && rdist->hd < rdist->vd) || rdist->vd == -1)
	{
		if (r->h.a >= 0 && r->h.a < M_PI)
			r->texture = data->no_texture;
		else
			r->texture = data->so_texture;
		td = rdist->hd;
		r->t = r->h;
	}
	else if ((rdist->vd != -1 && rdist->vd < rdist->hd) || rdist->hd == -1)
	{
		if (r->h.a >= M_PI / 2 && r->h.a < M_PI + (M_PI / 2))
			r->texture = data->we_texture;
		else
			r->texture = data->ea_texture;
		td = rdist->vd;
		r->t = r->v;
	}
	return (td);
}

void	free_raycast(t_rays *r, t_raydist *rdist)
{
	free(r->v.txt);
	free(r->p);
	free(rdist->td);
}

void	raycast(t_data *data)
{
	int			i;
	float		ca;
	double		dr;
	t_rays		r;
	t_raydist	rdist;

	r = rays_struct_init();
	rdist = rdist_struct_init(data);
	i = 0;
	dr = (80 / (double)data->win_w) * DR;
	while (i < data->win_w)
	{
		rays_init(data, dr, i, &r);
		rdist.hd = horizontalcheck(data, &r.h);
		rdist.vd = verticalcheck(data, &r.v);
		rdist.td[i] = totalcheck(data, &rdist, &r);
		ca = data->player->a - r.h.a;
		ca = limit_angle(ca);
		rdist.td[i] = rdist.td[i] * cos(ca);
		r.t.txt = r.texture;
		draw_walls(data, &rdist, i, &r.t);
		i++;
	}
	put_sprites(data, &rdist);
	free_raycast(&r, &rdist);
}
