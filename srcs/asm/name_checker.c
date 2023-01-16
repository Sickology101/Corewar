/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:28:58 by marius            #+#    #+#             */
/*   Updated: 2023/01/16 20:13:54 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

// checks the first char of the line to see if it is a comment
bool	check_comment(char *str)
{
	if (str[0] == '#')
		return (true);
	return (false);
}

int	search_char(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index] != c && str[index] != '\0')
	{
		index++;
	}
	if (str[index] == '\0')
		return (0);
	else
		return (index);
}

int	check_valid_format(char *str)
{
	int	index;

	index = search_char(str, '"');
	while (str[++index] != '"')
	{
		if (str[index] == '\0')
			return (false);
	}
	return (true);
}

// checks if the name is on 1 line
bool	check_1_line(char *str)
{
	int	index;

	index = 0;
	index = search_char(str, '"');
	if (str[++index] == '\0' || index == 0)
		return (false);
	else
	{
		while (str[index] != '\0')
		{
			if (str[index] == '"')
			{
				if (str[++index] == '\0')
					return (true);
				else
				{
					index = ignore_spaces(str, index);
					if (str[index] == '\0' || str[index] == COMMENT_CHAR)
						return (true);
					else
						return (false);
				}
			}
			index++;
		}
		if (str[index] == '\0')
			return (false);
	}
	return (true);
}

//gets the name of the champion and makes sure it is correctly formatted
char	*get_name(int fd, char *line)
{
	int		index;
	char	*dest;
	int		ret;

	index = ft_strlen(line);
	dest = ft_strdup(line);
	if (check_1_line(line))
		return (dest);
	else
		exit_usage(1);
	ret = 1;
	if (!check_valid_format(line))
		exit_usage(0);
	while (ret)
	{
		free(line);
		ret = get_next_line(fd, &line);
		index = ft_strlen(line);
		dest = ft_strupdate(dest, "\n");
		dest = ft_strupdate(dest, line);
		if (line[--index] == '"')
			return (dest);
	}
	exit_usage(0);
	return (NULL);
}