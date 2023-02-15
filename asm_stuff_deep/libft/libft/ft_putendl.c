/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:07:12 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/09 11:07:13 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(char const *s)
{
	size_t	index;
	char	c;

	index = 0;
	while (s[index] != '\0')
	{
		write(1, &s[index], 1);
		index++;
	}
	c = '\n';
	write(1, &c, 1);
}
