/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:19:50 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/08 16:19:51 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i1;
	size_t	i2;
	size_t	t;

	i1 = 0;
	while (i1 < len && haystack[i1] != '\0')
	{
		i2 = 0;
		t = i1;
		while (haystack[t] == needle[i2] && haystack[t] != '\0'
			&& needle[i2] != '\0' && t < len)
		{
			t++;
			i2++;
		}
		if (needle[i2] == '\0')
			return (&((char *)haystack)[t - i2]);
		i1++;
	}
	if (needle[0] == '\0')
		return ((char *)haystack);
	return (NULL);
}
