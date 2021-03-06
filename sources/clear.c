/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 19:15:31 by asaboure          #+#    #+#             */
/*   Updated: 2021/10/01 16:21:49 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../minilibx-linux/mlx.h"

void	clear_image(t_imgdata *img, void *mlx)
{
	if (img->path)
		free(img->path);
	if (img->img)
		mlx_destroy_image(mlx, img->img);
	free (img);
}
