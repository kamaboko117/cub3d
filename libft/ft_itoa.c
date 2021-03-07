/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:05:04 by asaboure          #+#    #+#             */
/*   Updated: 2019/11/23 18:39:46 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*neg(unsigned int n, unsigned int temp)
{
	char	*ret;
	int		i;

	i = 2;
	while (temp >= 10)
	{
		i++;
		temp = temp / 10;
	}
	if (!(ret = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ret[i] = '\0';
	ret[0] = '-';
	while (i-- > 2)
	{
		if (n >= 10)
		{
			ret[i] = (n % 10) + 48;
			n = n / 10;
		}
		if (n < 10)
			ret[i - 1] = n + 48;
	}
	return (ret);
}

static char	*pos(int n)
{
	char	*ret;
	int		temp;
	int		i;

	temp = n;
	i = 1;
	while (temp >= 10)
	{
		i++;
		temp = temp / 10;
	}
	if (!(ret = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ret[i] = '\0';
	while (i-- > 1)
	{
		if (n >= 10)
		{
			ret[i] = (n % 10) + 48;
			n = n / 10;
		}
		if (n < 10)
			ret[i - 1] = n + 48;
	}
	return (ret);
}

char		*ft_itoa(int n)
{
	char	*ret;

	if (n <= -10)
		ret = neg(-n, -n);
	if (n >= 10)
		ret = pos(n);
	if (n < 10 && n >= 0)
	{
		if (!(ret = (char *)malloc(sizeof(char) * 2)))
			return (NULL);
		ret[1] = '\0';
		ret[0] = n + 48;
	}
	if (n < 0 && n > -10)
	{
		if (!(ret = (char *)malloc(sizeof(char) * 3)))
			return (NULL);
		ret[0] = '-';
		ret[1] = -n + 48;
		ret[2] = '\0';
	}
	return (ret);
}
