/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 09:13:26 by marius            #+#    #+#             */
/*   Updated: 2022/12/10 17:23:39 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*ptr;
	size_t	index;

	ptr = ft_strnew(n);
	if (!ptr)
		return (NULL);
	index = 0;
	while (s1[index] && index < n)
	{
		ptr[index] = s1[index];
		++index;
	}
	return (ptr);
}
