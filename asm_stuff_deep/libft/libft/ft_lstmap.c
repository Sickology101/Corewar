/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:59:39 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/11 13:59:40 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	freelist(t_list	*first)
{
	while (first)
	{
		free(first->content);
		first->content = NULL;
		first->content_size = 0;
		first = first->next;
	}
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*first;
	t_list	*new;

	if ((!(lst)) || (!(f)))
		return (NULL);
	new = ft_lstnew(f(lst)->content, f(lst)->content_size);
	if (new == NULL)
		return (NULL);
	first = new;
	while (lst->next != NULL)
	{
		lst = lst->next;
		new->next = ft_lstnew(f(lst)->content, f(lst)->content_size);
		if (new->next == NULL)
			freelist(first);
		new = new->next;
	}
	return (first);
}

/*
t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*first;
	t_list	*new;

	if ((!(lst)) || (!(f)))
		return (NULL);
	new = f(lst);
	if (new == NULL)
		return (NULL);
	first = new;
	while (lst->next != NULL)
	{
		lst = lst->next;
		new->next = f(lst);
		if (new->next == NULL)
			return (NULL);
		new = new->next;
	}
	return (first);
}










t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*first;
	t_list	*new;
	t_list	*temp;

	if ((!(lst)) || (!(f)))
		return (NULL);
	new = ft_lstnew(f(lst)->content, f(lst)->content_size);
	if (!new)
		return (NULL);
	first = new;
	temp = lst->next;
	while (!temp)
	{
		new = new->next;
		new = ft_lstnew(f(temp)->content, f(temp)->content_size);
		if (!new)
		{
			freelist(first);
		}
		temp = temp->next;
	}
	return (first);
}*/
