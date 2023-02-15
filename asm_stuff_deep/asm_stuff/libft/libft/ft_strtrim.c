/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:32:01 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/08 19:32:02 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	trimstart(const char *s)
{
	size_t	index;

	index = 0;
	while (s[index] == ' ' || s[index] == '\t' || s[index] == '\n')
	{
		index++;
	}
	return (index);
}

static	size_t	trimend(const char *s)
{
	size_t	index;

	index = 0;
	while (s[index] != '\0')
		index++;
	index--;
	while (s[index] == ' ' || s[index] == '\t' || s[index] == '\n')
	{
		if (index == 0)
			break ;
		index--;
	}
	return (index);
}

static	char	*assign_string(char *dest, const char *s, size_t b, size_t e)
{
	size_t	index;

	index = 0;
	while (b <= e)
	{
		dest[index] = s[b];
		index++;
		b++;
	}
	dest[index] = '\0';
	return (dest);
}

char	*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;
	char	*dest;

	start = trimstart(s);
	end = trimend(s);
	if (end < start || ft_strlen(s) == 0)
	{
		dest = (char *)malloc(sizeof(char) * 1);
		dest[0] = '\0';
		return (dest);
	}
	dest = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!dest)
		return (NULL);
	dest = assign_string(dest, s, start, end);
	return (dest);
}

/*static	size_t	trimlenght(const char *s)
{
	size_t	index;
	size_t	size;

	index = 0;
	size = 0;
	while (s[index] == ' ' || s[index] == '\t' || s[index] == '\n')
	{
		index++;
	}
	while (s[index] != '\0')
	{
		index++;
		size++;
	}
	if (size == 0)
		return (size);
	index--;
	while (s[index] == ' ' || s[index] == '\t' || s[index] == '\n')
	{
		index--;
		size--;
	}
	return (size);
}

static	void	trimend(char *dest, size_t index2)
{
	index2--;
	while (dest[index2] == ' ' || dest[index2] == '\t' || dest[index2] == '\n')
	{
		dest[index2] = '\0';
		index2--;
	}
}

char	*ft_strtrim(char const *s)
{
	size_t	index1;
	size_t	index2;
	char	*dest;

	dest = (char *)malloc(sizeof(char) * trimlenght(s) + 1);
	if (trimlenght(s) == 0)
	{
		dest[0] = '\0';
		return (dest);
	}
	if (!dest)
		return (NULL);
	index1 = 0;
	while (s[index1] == ' ' || s[index1] == '\t' || s[index1] == '\n')
		index1++;
	index2 = 0;
	while (s[index1] != '\0')
	{
		dest[index2] = s[index1];
		index1++;
		index2++;
	}
	dest[index2] = '\0';
	trimend(dest, index2);
	return (dest);
}*/
