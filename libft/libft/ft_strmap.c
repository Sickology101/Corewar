/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:51:34 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/09 10:51:35 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	size_t	index;
	size_t	size;
	char	*dest;

	size = ft_strlen((char *)s);
	dest = (char *)malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	index = 0;
	while (s[index] != '\0')
	{
		dest[index] = f(s[index]);
		index++;
	}
	dest[index] = '\0';
	return (dest);
}
