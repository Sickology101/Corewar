/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:50:23 by marius            #+#    #+#             */
/*   Updated: 2023/01/12 15:05:19 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
// checks the first char of the line to see if it is a comment
int	check_comment(char *str)
{
	if (str[0] == '#')
		return (1);
	return (0);
}

int	search_char(char *str, char c)
{
	int index;

	index = 0;
	while (str[index] != c && str[index] != '\n')
	{
		index++;
	}
	if (str[index] == '\n')
		return(0);
	else
		return (index);
}

int	check_valid(char *str)
{
	int	index;
	
	index = search_char(str, '"');
	while(str[++index] != '"')
	{
		if (str[index] == '\n')
			return (1);
	}
	return (0);
}

int	check_quotes(char *str)
{
	int index;

	index = search_char(str, '"');
	if (str[++index] == '\0')
		return (0);
	else
		return (1);
}

//gets the name of the champion and makes sure it is correctly formatted
char *get_name(int fd, char *line)
{
	int index;
	char *dest;
	int ret;

	index = ft_strlen(line);
	dest = ft_strdup(line);
	if (line[--index] == '"' && check_quotes(line))
		return (dest);
	ret = 1;
	if (check_valid(line))
		exit_usage();
	while(ret)
	{
		free(line);
		ret = get_next_line(fd,&line);
		index = ft_strlen(line);
		dest = ft_strupdate(dest, "\n");
		dest = ft_strupdate(dest, line);
		if (line[--index] == '"')
			return(dest);
	}
	exit_usage();
	return (NULL);
}

//this function reads through the first line and saves the name on data->file[0]
// and the comment on data->file[1]
int	get_name_comment(t_data *data, int fd)
{
	int ret;
	char *line;

	ret = get_next_line(fd, &line);
	if (ret == 0)
		return (1);
	while (check_comment(line))
	{
		ret = get_next_line(fd, &line);
		if (ret == 0)
			return (1);
	}
	if (!ft_strncmp(line, ".name", 5))
		data->file[0] = get_name(fd,line);
	else if (!ft_strncmp(line, ".comment", 8))
		data->file[1] = get_name(fd,line);
	ret = get_next_line(fd, &line);
	while (check_comment(line))
	{
		ret = get_next_line(fd, &line);
		if (ret == 0)
			return (1);
	}
	if (!ft_strncmp(line, ".name", 5))
		data->file[0] = get_name(fd,line);
	else if (!ft_strncmp(line, ".comment", 8))
		data->file[1] = get_name(fd,line);
	return (0);
}

// this function ignores empty lines
int	check_empty_line(char *str)
{
	if (str[0] == '\0')
		return (1);
	else
		return (0);
}

char *check_valid_inst(char *line)
{
	char *dest;

	dest = ft_strdup(line);
	return (dest);
}

// this functions continues reading the file and saves each instruction
// at the same time checking if it valid?
int	get_instructions(t_data *data, int fd)
{
	char	*line;
	int		ret;
	int		index;
	
	ret = 1;
	index = 2;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		while (check_comment(line) || check_empty_line(line))
		{
			ret = get_next_line(fd, &line);
			if (ret == 0)
				return (1);
		}
		data->file[index++] = check_valid_inst(line);
	}
	return (0);
}

//a function that reads through the file and checks the syntax
//returns 1 if an error was found
int scan_file(t_data *data, int fd)
{
	int index;
	
	data->file = (char **)malloc(sizeof(char *) * 1064);
	if (get_name_comment(data, fd))
		return (1);
	if (get_instructions(data, fd))
		return (1);
	index = 0;
	while (data->file[index] != NULL)
	{
		ft_printf("%s\n",data->file[index++]);
	}
	return (0);
}