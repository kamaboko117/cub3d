#include "../cub3d.h"

double	dist(t_player *a, t_ray *b)
{
	return(sqrt((b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y)));
}

double	horizontalcheck(t_data *data, t_ray *r, int dof)
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
		return (dist(data->player, r));
	return (-1);
}

double	verticalcheck(t_data *data, t_ray *r, int dof)
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
		return(dist(data->player, r));
	return (-1);
}

void	raycast(t_data *data)
{
	int i;
	float	ca;
	int color;
	t_ray	rh;
	t_ray	rv;
	t_ray	rt;
	t_pos	m;
	t_raydist	rdist;
	
	i= 0;
	while (i < 80)
	{
		rh.a = data->player->a - DR * (40 - i);
		if (rh.a < 0)
			rh.a += 2 * M_PI;
		if (rh.a > 2 * M_PI)
			rh.a -= 2 * M_PI;
		rv.a = rh.a;
		rdist.hdist = horizontalcheck(data, &rh, 8);
		rdist.vdist = verticalcheck(data, &rv, 8);
		if ((rdist.hdist != -1 && rdist.hdist < rdist.vdist) || rdist.vdist == -1)
		{
			//imgdrawray(data, &rh, 0x00FF00);
			rdist.tdist = rdist.hdist;
			rt = rh;
			color = 0x00FF00;
		}
		else if ((rdist.vdist != -1 && rdist.vdist < rdist.hdist) || rdist.hdist == -1)
		{
			//imgdrawray(data, &rv, 0xFF0000);
			rdist.tdist = rdist.vdist;
			rt = rv;
			color = 0xFF0000;
		}
		ca = data->player->a - rh.a;
		if (ca < 0)
			ca += 2 * M_PI;
		if (ca > 2 * M_PI)
			ca -= 2 * M_PI;
		rdist.tdist = rdist.tdist * cos(ca);
		draw_walls(data, rdist, i, data->no_texture, &rt);
		i++;
	}
}
