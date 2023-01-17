/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:28:58 by marius            #+#    #+#             */
/*   Updated: 2023/01/17 10:44:03 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

bool	search_1_quote(char *str)
{
	int	index;

	index = search_char(str, '"');
	if (index == 0)
		return (false);
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
		if (search_1_quote(dest))
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
		else
			exit_usage(1);
	}
	return (dest);
}

//this function reads through the first line and saves the name on data->file[0]
// and the comment on data->file[1]
bool	get_name_comment(t_parser *data, int fd)
{
	int		ret;
	char	*line;

	ret = get_next_line(fd, &line);
	if (ret == 0)
		return (false);
	while (check_comment(line))
	{
		ret = get_next_line(fd, &line);
		if (ret == 0)
			return (false);
	}
	if (!ft_strncmp(line, ".name", 5))
		data->file[0] = get_name(fd, line);
	else if (!ft_strncmp(line, ".comment", 8))
		data->file[1] = get_name(fd, line);
	ret = get_next_line(fd, &line);
	while (check_comment(line))
	{
		ret = get_next_line(fd, &line);
		if (ret == 0)
			return (false);
	}
	if (!ft_strncmp(line, ".name", 5))
		data->file[0] = get_name(fd, line);
	else if (!ft_strncmp(line, ".comment", 8))
		data->file[1] = get_name(fd, line);
	return (true);
}