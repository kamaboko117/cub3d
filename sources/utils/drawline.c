/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:26:09 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/08 19:40:51 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	line_parameters(t_line *params, t_pos a, t_pos b)
{
	if (a.y < b.y)
		params->sign_y = 1;
	else
		params->sign_y = -1;
	if (a.x < b.x)
		params->sign_x = 1;
	else
		params->sign_x = -1;
	params->delta_y = abs(b.y - a.y);
	params->delta_x = abs(b.x - a.x);
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
