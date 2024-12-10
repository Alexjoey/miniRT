/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:06:12 by amylle            #+#    #+#             */
/*   Updated: 2023/10/28 16:18:23 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*prev;
	t_list	*new;
	t_list	*root;

	root = NULL;
	while (lst)
	{
		if (f != NULL && lst->content != NULL)
			new = ft_lstnew((*f)(lst->content));
		if (!new)
			return (NULL);
		ft_lstadd_back(&root, new);
		prev = lst;
		lst = lst->next;
		if (del != NULL)
			(del)(prev);
	}
	return (root);
}
