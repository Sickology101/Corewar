/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:28:58 by marius            #+#    #+#             */
/*   Updated: 2023/01/16 21:05:09 by marius           ###   ########.fr       */
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

bool	check_valid_format(char *str)
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

// checks that there are 2 " in the string
bool	search_quotes(char *str)
{
	int index;
	int	flag;

	index = 0;
	flag = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '"')
			flag++;
		if (flag == 2)
			return (true);
		index++;
	}
	return (false);
}

//gets the name of the champion and makes sure it is correctly formatted
char	*get_name(int fd, char *line)
{
	char	*dest;
	int		ret;

	dest = ft_strdup(line);
	if (search_quotes(dest))
	{
		if (!check_1_line(line))
			exit_usage(1);
	}
	else
	{
		ret = 1;
		if (!check_valid_format(dest))
		{
			while (ret)
			{
				free(line);
				ret = get_next_line(fd, &line);
				dest = ft_strupdate(dest, "\n");
				dest = ft_strupdate(dest, line);
				if (search_quotes(dest))
				{
					if (!check_1_line(dest))
						exit_usage(1);
					else
						break ;
				}
					
			}
		}
	}
	return (dest);
}