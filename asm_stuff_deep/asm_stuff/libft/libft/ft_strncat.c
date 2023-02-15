/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:09:10 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/08 15:09:11 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	index1;
	size_t	index2;

	index1 = 0;
	while (s1[index1] != '\0')
	{
		index1++;
	}
	index2 = 0;
	while (index2 < n && s2[index2] != '\0')
	{
		s1[index1] = s2[index2];
		index1++;
		index2++;
	}
	s1[index1] = '\0';
	return (s1);
}
