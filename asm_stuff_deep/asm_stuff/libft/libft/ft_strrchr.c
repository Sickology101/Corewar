/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:09:46 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/15 12:09:48 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	index;
	void	*temp;
	int		temp_index;

	index = 0;
	temp_index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == c)
		{
			temp = &((char *)s)[index];
			temp_index++;
		}
		index++;
	}
	if (s[index] == c)
	{
		temp = &((char *)s)[index];
		temp_index++;
	}
	if (temp_index != 0)
		return (temp);
	else
		return (NULL);
}
