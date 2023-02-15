/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:39:30 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/08 12:39:31 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	putmin(void)
{
	char	c;

	c = '-';
	write(1, &c, 1);
	c = '2';
	write(1, &c, 1);
	return (147483648);
}

static	void	printnumber(int n, size_t index)
{
	char	c;

	while (n != 0 || index != 0)
	{
		c = n / index + '0';
		write(1, &c, 1);
		n = n % index;
		index = index / 10;
	}
}

void	ft_putnbr(int n)
{
	size_t	index;
	int		temp;

	index = 1;
	if (n == -2147483648)
		n = putmin();
	if (n < 0)
	{
		ft_putchar('-');
		n = n * (-1);
	}
	temp = n;
	while (temp > 9)
	{
		temp = temp / 10;
		index = index * 10;
	}
	printnumber(n, index);
}
