/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:04:09 by asaboure          #+#    #+#             */
/*   Updated: 2020/02/04 18:48:35 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	ft_recurr(int n, int fd)
{
	char a;

	if (n <= -10)
	{
		ft_recurr(n / 10, fd);
		ft_recurr(n % 10, fd);
	}
	else
	{
		a = -n + 48;
		write(fd, &a, 1);
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	{
		if (n < 0)
			write(fd, "-", 1);
		else
			n = -n;
		ft_recurr(n, fd);
	}
}
