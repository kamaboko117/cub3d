/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:18:39 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/23 18:06:50 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	rays_init(t_data *data, double dr, int i, t_rays *r)
{
	r->h.a = data->player->a - dr * ((data->win_w / 2) - i);
	r->h.a = limit_angle(r->h.a);
	r->v.a = r->h.a;
}

t_raydist	rdist_struct_init(t_data *data)
{
	t_raydist	rdist;

	rdist.td = (double *)malloc(sizeof(double) * data->win_w);
	rdist.hd = 0;
	rdist.vd = 0;
	return (rdist);
}
