/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:34:13 by mangheli          #+#    #+#             */
/*   Updated: 2023/02/16 17:10:02 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

static int	skip_front(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '-')
	{
		*sign = -1;
		++i;
	}
	else if (str[i] == '+')
		++i;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		i;
	long	n;
	size_t	count;

	sign = 1;
	i = skip_front(str, &sign);
	n = 0;
	count = 0;
	while (ft_isdigit(str[i]))
	{
		n = 10 * n + (str[i] - '0');
		if (count >= 18)
		{
			if (n > MAX_INT && sign != -1)
				return (-1);
			else if (sign == -1 && n > ((long)MAX_INT + 1))
				return (0);
		}
		++i;
		++count;
	}
	return ((int)n * sign);
}
