/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 13:51:35 by asaboure          #+#    #+#             */
/*   Updated: 2019/11/27 17:26:01 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char		*ft_strdupsplit(char const *s, char c)
{
	size_t	i;
	char	*cpy;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!((cpy = (char *)malloc(sizeof(char) * i + 1))))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

static char		**tabinit(char **ret, char const *s, char c)
{
	size_t	n;
	size_t	i;

	n = 1;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			n++;
		i++;
	}
	if (!(ret = (char **)malloc(sizeof(char *) * (n + 1))))
		return (NULL);
	return (ret);
}

char			**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**ret;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	ret = NULL;
	if (!(ret = tabinit(ret, s, c)))
		return (NULL);
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			if (!(ret[j] = ft_strdupsplit(s + i, c)))
				return (NULL);
			j++;
			i += ft_strlen(ret[j - 1]);
		}
		i++;
	}
	ret[j] = NULL;
	return (ret);
}
