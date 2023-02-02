/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 05:22:04 by marius            #+#    #+#             */
/*   Updated: 2023/02/02 12:10:13 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int	get_label_size(char *line, int index)
{
	while (line[index] != '\0' && line[index] != LABEL_CHAR)
	{
		index++;
	}
	if (line[index] == '\0')
		exit_usage(1);
	return (index);
}

bool	check_valid_label_char(char c)
{
	int	index;

	index = 0;
	while (index < 38)
	{
		if (c == LABEL_CHARS[index])
			return (true);
		index++;
	}
	return (false);
}

char *get_label(char *line, int *index)
{
	int	size;
	char *dest;

	size = get_label_size(line, *index);
	dest = (char *)malloc(sizeof(char) * size);
	dest[size] = '\0';
	while (*index < size)
	{
		if (!check_valid_label_char(line[*index]))
			exit_usage(2);
		dest[*index] = line[*index];
		*index = *index + 1;
	}
	return (dest);
}

void	save_instruction(t_parser *data, char *line)
{
	int	index;

	index = 0;
	if (line[index] != MTY_SPACE_1 && line[index] != MTY_SPACE_2)
	{
		data->line[data->file_size]->label = get_label(line, &index);
		index++;
		data->line[data->file_size]->type = 0;
		data->line[data->file_size]->size = 0;
		index = ignore_spaces(line, index);
		if (line[index] != '\0' && line[index] != COMMENT_CHAR)
		{
			get_statement(data, line, index);
			data->line[data->file_size]->type = 2;
		}
			
		data->file_size++;
	}
	else
	{
		index = ignore_spaces(line, index);
		data->line[data->file_size]->label = NULL;
		data->line[data->file_size]->type = 1;
		get_statement(data, line, index);
		data->file_size++;
	}
		//data->line[data->file_size]->label = get_label(line, &index);
}

void	get_instructions(t_parser *data)
{
	char *line;
	int		ret;

	ret = get_next_line(data->fd, &line);
	data->file_size = 2;
	while(ret != 0)
	{
		if (!ignore_comment_empty(line))
		{
			data->line[data->file_size] = (t_line *)malloc(sizeof(t_line));
			data->line[data->file_size]->str = (char *)malloc(sizeof(char) * ft_strlen(line));
			data->line[data->file_size]->str = ft_strcpy(data->line[data->file_size]->str, line);
			save_instruction(data, line);
		}
			
		ret = get_next_line(data->fd, &line);
	}
	if (data->file_size == 2)
		exit_usage(4);
}