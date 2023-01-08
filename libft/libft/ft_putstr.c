/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:29:35 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/03 12:29:38 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char const *s)
{
	int		index;
	char	c;

	index = 0;
	while (s[index] != '\0')
	{
		c = s[index];
		write(1, &c, 1);
		index++;
	}
}
