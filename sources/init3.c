/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:18:39 by asaboure          #+#    #+#             */
/*   Updated: 2021/07/05 17:18:53 by asaboure         ###   ########.fr       */
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
