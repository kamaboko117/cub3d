/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:31:57 by asaboure          #+#    #+#             */
/*   Updated: 2019/12/04 19:48:04 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*new;

	if (lst == NULL)
		return (NULL);
	ret = NULL;
	while (lst)
	{
		if (!(new = ft_lstnew(f(lst->content))))
			ft_lstclear(&ret, del);
		ft_lstadd_back(&ret, new);
		lst = lst->next;
	}
	return (ret);
}
