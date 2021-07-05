/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:26:09 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/05 19:29:25 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	line_parameters(t_line *params, t_pos a, t_pos b)
{
	params->sign_y = (a.y < b.y ? 1 : -1);
	params->sign_x = (a.x < b.x ? 1 : -1);
	params->delta_y = fabs(b.y - a.y);
	params->delta_x = fabs(b.x - a.x);
	params->offset = params->delta_x - params->delta_y;
	params->error = 0;
}

void	imgdrawline(t_pos a, t_pos b, t_data *data)
{
	t_pos	p;
	t_line	params;

	line_parameters(&params, a, b);
	p = a;
	while (p.y != b.y || p.x != b.x)
	{
		imgputpixel(data->img, p.x, p.y, p.color);
		params.error = params.offset * 2;
		if (params.error > -params.delta_y)
		{
			params.offset -= params.delta_y;
			p.x += params.sign_x;
		}
		if (params.error < params.delta_x)
		{
			params.offset += params.delta_x;
			p.y += params.sign_y;
		}
	}
	imgputpixel(data->img, p.x, p.y, p.color);
}
