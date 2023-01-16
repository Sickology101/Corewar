/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:50:23 by marius            #+#    #+#             */
/*   Updated: 2023/01/14 15:21:03 by marius           ###   ########.fr       */
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
	while (str[index] != c && str[index] != '\n')
	{
		index++;
	}
	if (str[index] == '\n')
		return (false);
	else
		return (index);
}

int	check_valid(char *str)
{
	int	index;

	index = search_char(str, '"');
	while (str[++index] != '"')
	{
		if (str[index] == '\n')
			return (false);
	}
	return (true);
}

bool	check_quotes(char *str)
{
	int	index;

	index = search_char(str, '"');
	if (str[++index] == '\0')
		return (false);
	else
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
	if (line[--index] == '"' && check_quotes(line))
		return (dest);
	ret = 1;
	if (!check_valid(line))
		exit_usage();
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
	exit_usage();
	return (NULL);
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

// this function ignores empty lines
int	check_empty_line(char *str)
{
	if (str[0] == '\0')
		return (true);
	else
		return (false);
}

int	check_valid_label_char(char c)
{
	int	index;

	index = 0;
	while (index < 38)
	{
		if (c == LABEL_CHAR[index])
			return (0);
		index++;
	}
	ft_printf("%c\n", c);
	return (1);
}

// checks the line from index (0 for statement line)
// to see if it follows a valid statement (name, argnumb, and arg type)
bool	check_valid_state(char *line, int index)
{
	while (line[index] != '\n')
	{
		while (line[index] == '	' || line[index] == ' ')
		{
			// HERE
			index++;
		}
	}
}

// checks the line and reads through the first chars up to ':'
// to see if they are valid LABEL_CHARs then checks the rest of it to see
// if it is a valid statement
bool	check_valid_label(char *line)
{
	int	index;

	index = 0;
	while (line[index] != ':')
	{
		if (check_valid_label_char(line[index]))
			return (false);
		index++;
	}
	if (line[index++] == '\n')
		return (true);
	else if (check_valid_state(line, index))
		return (false);
	return (true);
}

// verifies every line if it is a valid(lexically) statement or label
char	*check_valid_inst(char *line)
{
	char	*dest;

	dest = NULL;
	if (line[0] == '	' || line[0] == ' ')
		dest = ft_strdup("OK");
	else
	{
		if (check_valid_label(line))
			dest = ft_strdup(line);
		else
			exit_usage();
	}
	return (dest);
}

// this functions continues reading the file and saves each instruction
// at the same time checking if it valid?
bool	get_instructions(t_parser *data, int fd)
{
	char	*line;
	int		ret;
	int		index;

	ret = 1;
	index = 2;
	init_statements(data);
	while (ret)
	{
		ret = get_next_line(fd, &line);
		while (check_comment(line) || check_empty_line(line))
		{
			ret = get_next_line(fd, &line);
			if (ret == 0)
				return (false);
		}
		if (ret == 0)
			break ;
		data->file[index++] = check_valid_inst(line);
	}
	return (true);
}

//a function that reads through the file and checks the syntax
//returns 1 if an error was found
int	scan_file(t_parser *data, int fd)
{
	int	index;

	data->file = (char **)malloc(sizeof(char *) * 1064);
	if (!get_name_comment(data, fd))
		return (false);
	if (!get_instructions(data, fd))
		return (false);
	index = 0;
	while (data->file[index] != NULL)
	{
		ft_printf("%s\n", data->file[index++]);
	}
	return (true);
}
