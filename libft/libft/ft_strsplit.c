/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:46:39 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/11 10:46:40 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	numberofstrings(char const *s, char c)
{
	size_t	index;
	size_t	size;

	index = 0;
	size = 0;
	while (s[index] != '\0')
	{
		if (s[index] != c && (s[index + 1] == c || s[index + 1] == '\0'))
			size++;
		index++;
	}
	if (size == 0)
		size++;
	return (size);
}

static	size_t	stringlenght(char const *s, char c, size_t index)
{
	size_t	size;

	size = 0;
	while (s[index] != c)
	{
		size++;
		index++;
	}
	return (size);
}

static	size_t	assignstring(char const *s, char *dest, char c, size_t index)
{
	size_t	index1;

	index1 = 0;
	while (s[index] != c && s[index] != '\0')
	{
		dest[index1] = s[index];
		index1++;
		index++;
	}
	dest[index1] = '\0';
	return (index);
}

static	char	**extrafunction(char **dest, char const *s, char c)
{
	size_t	index;
	size_t	index1;
	size_t	size;

	index = 0;
	index1 = 0;
	while (s[index] != '\0')
	{
		if (s[index] != c)
		{
			size = stringlenght(s, c, index);
			dest[index1] = (char *)malloc(sizeof(char) * size + 1);
			if (!dest[index1])
				return (NULL);
			index = assignstring(s, dest[index1], c, index);
			index1++;
		}
		if (s[index] != '\0')
			index++;
	}
	dest[index1] = NULL;
	return (dest);
}

char	**ft_strsplit(char const *s, char c)
{
	size_t	size;
	char	**dest;

	size = numberofstrings(s, c);
	dest = (char **)malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	dest = extrafunction(dest, s, c);
	if (size == 0)
		size++;
	dest[size] = 0;
	return (dest);
}
