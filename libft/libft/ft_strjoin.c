/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:20:00 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/08 19:20:01 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	joinstrings(char const *s1, char const *s2, char *dest)
{
	size_t	index1;
	size_t	index2;

	index1 = 0;
	index2 = 0;
	while (s1[index2] != '\0')
	{
		dest[index1] = s1[index2];
		index1++;
		index2++;
	}
	index2 = 0;
	while (s2[index2] != '\0')
	{
		dest[index1] = s2[index2];
		index1++;
		index2++;
	}
	dest[index1] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	joinstrings(s1, s2, dest);
	return (dest);
}
