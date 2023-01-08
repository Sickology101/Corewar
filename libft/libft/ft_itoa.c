/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 09:52:58 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/09 09:52:59 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	checksize(int n)
{
	size_t	size;
	long	temp;

	size = 0;
	temp = n;
	if (temp == 0)
		size = 1;
	while (temp != 0)
	{
		if (temp < 0)
		{
			size++;
			temp = temp * (-1);
		}
		temp = temp / 10;
		size++;
	}
	return (size);
}

static	char	*assignstr(char *dest, long temp, size_t size)
{
	if (temp < 0)
	{
		dest[0] = '-';
		temp = temp * (-1);
	}
	dest[size] = '\0';
	size--;
	while (temp != 0)
	{
		dest[size] = temp % 10 + '0';
		temp = temp / 10;
		size --;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	char	*dest;
	size_t	size;
	long	temp;

	size = checksize(n);
	dest = (char *)malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	if (n == 0)
	{
		dest[0] = '0';
		dest[1] = '\0';
		return (dest);
	}
	temp = n;
	dest = assignstr(dest, temp, size);
	return (dest);
}
