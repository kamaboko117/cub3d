/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:04:44 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/06 18:04:45 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"
#include "../../libft/libft.h"

void	get_resolution(char *line, int *width, int *height)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isdigit(line[i]))
		i++;
	*width = ft_atoi(line + i);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	while (line[i] && !ft_isdigit(line[i]))
		i++;
	*height = ft_atoi(line + i);
}
