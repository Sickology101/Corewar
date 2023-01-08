/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:33:45 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/04 11:33:48 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
	{
		((char *)dst)[index] = ((char *)src)[index];
		if (((unsigned char *)src)[index] == (unsigned char)c)
			return ((unsigned char *)dst + index + 1);
		index++;
	}
	return (NULL);
}
