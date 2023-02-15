/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:13:05 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/08 15:13:06 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	assignsize(char *dst, const char *src, size_t dstsize)
{
	size_t	size;

	if (ft_strlen(dst) < dstsize)
		size = ft_strlen(dst) + ft_strlen(src);
	else
		size = dstsize + ft_strlen(src);
	return (size);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	index1;
	size_t	index2;
	size_t	max;
	size_t	size;

	index1 = 0;
	size = assignsize(dst, src, dstsize);
	if (ft_strlen(dst) >= dstsize)
		return (size);
	while (dst[index1] != '\0')
	{
		index1++;
	}
	index2 = 0;
	max = dstsize - ft_strlen(dst) - 1;
	while (index2 < max && src[index2] != '\0')
	{
		dst[index1] = src[index2];
		index1++;
		index2++;
	}
	dst[index1] = '\0';
	return (size);
}
