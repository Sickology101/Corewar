/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:34:13 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/08 16:34:14 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	index;
	int		i;
	int		sign;

	index = 0;
	i = 0;
	sign = 1;
	while (ft_emptyspace(str[index]) == 1)
	{
		index++;
	}
	if (str[index] == '-')
	{
		sign = -1;
		index++;
	}
	else
		if (str[index] == '+')
			index++;
	while (str[index] > 47 && str[index] < 58)
	{
		i = i * 10 + str[index] - '0';
		index++;
	}
	return (i * sign);
}
