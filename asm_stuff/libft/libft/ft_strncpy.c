/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:46:22 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/15 12:42:06 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *s1, size_t len)
{
	size_t	index;

	index = 0;
	while (index < len && s1[index] != '\0')
	{
		dest[index] = s1[index];
		index++;
	}
	while (index < len)
	{
		dest[index] = '\0';
		index++;
	}
	return (dest);
}
