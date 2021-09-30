/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:14:38 by asaboure          #+#    #+#             */
/*   Updated: 2021/09/30 14:59:09 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../minilibx-linux/mlx.h"

static void	set_texture(t_data *data, t_imgdata *texture)
{
	texture->img = mlx_xpm_file_to_image(data->mlx_ptr,
			texture->path,
			&texture->width,
			&texture->height);
	if (texture->img == NULL)
		exit_failure("Impossible to load a texture\n", data);
	texture->addr = mlx_get_data_addr(texture->img,
			&(texture->bpp),
			&(texture->line_len),
			&(texture->endian));
}

void	get_texture(t_data *data)
{
	set_texture(data, data->no_texture);
	set_texture(data, data->so_texture);
	set_texture(data, data->we_texture);
	set_texture(data, data->ea_texture);
	if (data->sp_texture->path)
		set_texture(data, data->sp_texture);
}
