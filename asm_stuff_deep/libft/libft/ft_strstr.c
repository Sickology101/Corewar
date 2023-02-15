/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:01:13 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/08 16:01:14 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	index1;
	size_t	index2;
	size_t	temp;

	index1 = 0;
	temp = 0;
	while (haystack[index1] != '\0')
	{
		index2 = 0;
		temp = index1;
		while (haystack[temp] == needle[index2] && haystack[temp] != '\0'
			&& needle[index2] != '\0')
		{
			temp++;
			index2++;
		}
		if (needle[index2] == '\0')
			return (&((char *)haystack)[temp - index2]);
		index1++;
	}
	if (needle[0] == '\0')
		return ((char *)haystack);
	return (NULL);
}
