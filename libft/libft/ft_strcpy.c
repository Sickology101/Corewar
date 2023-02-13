/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:29:07 by mangheli          #+#    #+#             */
/*   Updated: 2023/02/13 15:38:09 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *s1)
{
	size_t	index;

	index = 0;
	while (s1[index] != '\0')
	{
		dest[index] = s1[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}