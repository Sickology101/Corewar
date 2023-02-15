/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:40:25 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/11 10:40:26 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	putmin(int fd)
{
	char	c;

	c = '-';
	write(fd, &c, 1);
	c = '2';
	write(fd, &c, 1);
	return (147483648);
}

static	void	printnumber(int n, size_t index, int fd)
{
	char	c;

	while (n != 0 || index != 0)
	{
		c = n / index + '0';
		write(fd, &c, 1);
		n = n % index;
		index = index / 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	size_t	index;
	int		temp;

	index = 1;
	if (n == -2147483648)
		n = putmin(fd);
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = n * (-1);
	}
	temp = n;
	while (temp > 9)
	{
		temp = temp / 10;
		index = index * 10;
	}
	printnumber(n, index, fd);
}
