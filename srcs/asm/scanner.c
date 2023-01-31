/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:50:23 by marius            #+#    #+#             */
/*   Updated: 2023/01/31 09:17:31 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	scan_file(t_parser *data)
{
	data->line = (t_line **)malloc(sizeof(t_line *) * 1064);
	get_name_comment(data);
	get_instructions(data);
}

/*int	ignore_spaces(char *str, int index)
{
	while (str[index] != '\0' && (str[index] == MTY_SPACE_1 || str[index] == MTY_SPACE_2))
	{
		index++;
	}
	return (index);
}

// verifies every line if it is a valid(lexically) statement or label
char	*check_valid_inst(char *line, t_parser *data)
{
	char	*dest;

	dest = NULL;
	if (line[0] == MTY_SPACE_1 || line[0] == MTY_SPACE_2)
		if (check_valid_state(line,0, data))
			dest = ft_strdup(line);
		else
			exit_usage(3);
	else
	{
		if (check_valid_label(line, data))
			dest = ft_strdup(line);
		else
			exit_usage(2);
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
		data->file[index].line = check_valid_inst(line, data);
		data->file[index++].size = calculate_size(line, data);
		// a data->file[] resize required here if index > FILESIZE(now 1064)
	}
	data->file_size = index;
	return (true);
}

//a function that reads through the file and checks the syntax
//returns 1 if an error was found
int	scan_file(t_parser *data, int fd)
{
	int	index;

	data->file = (t_file *)malloc(sizeof(t_file) * 1064);
	data->label = (char **)malloc(sizeof(char *) * 128);
	if (!get_name_comment(data, fd))
		return (false);
	if (!get_instructions(data, fd))
		return (false);
	index = 0;
	while (data->file[index].line != NULL)
	{
		ft_printf("%s  size = %d\n", data->file[index].line, data->file[index++].size);
	}
	return (true);
}
*/