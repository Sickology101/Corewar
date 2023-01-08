/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:26:24 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/11 13:26:25 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp;
	t_list	*list;

	list = *alst;
	while (list != NULL)
	{
		temp = list->next;
		del(list->content, list->content_size);
		free(list);
		list = temp;
	}
	*alst = NULL;
}
