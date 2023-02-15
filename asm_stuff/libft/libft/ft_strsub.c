/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:11:20 by mangheli          #+#    #+#             */
/*   Updated: 2022/12/10 17:23:18 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	index;
	char	*dest;

	dest = (char *)malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	index = 0;
	while (index < len)
	{
		dest[index] = s[start];
		index++;
		start++;
	}
	dest[index] = '\0';
	return (dest);
}

char	*ft_chrsep(char **stringp, int ch)
{
	char	*ptr;

	ptr = ft_strchr(*stringp, ch);
	if (ptr)
	{
		*ptr = '\0';
		ptr++;
	}
	return (ptr);
}
