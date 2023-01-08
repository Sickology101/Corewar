/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 10:57:59 by marius            #+#    #+#             */
/*   Updated: 2022/04/05 13:48:58 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	checksize(unsigned int n)
{
	size_t			size;
	unsigned int	temp;

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

static	char	*assignstr(char *dest, unsigned int temp, size_t size)
{
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

char	*ft_utoa(unsigned int n)
{
	char			*dest;
	size_t			size;
	unsigned int	temp;

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
