/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:45:58 by marius            #+#    #+#             */
/*   Updated: 2023/01/19 11:07:49 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

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

char *get_label_name(char *line, int size)
{
	char *dest;
	int		index;

	dest = (char *)malloc(sizeof(char) * (size + 1));
	index = 0;
	while (index < size)
	{
		dest[index] = line[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

int	get_size(char *line, int index)
{
	int	size;

	size = 0;
	while(line[index] != MTY_SPACE_1 && line[index] != MTY_SPACE_2)
	{
		size++;
		index++;
	}
	return (size);
}

char	*get_instruction_name(char *line, int *index)
{
	char *dest;
	int		size;
	int		i;

	size = get_size(line, *index);
	dest = (char *)malloc(sizeof(char) * size);
	dest[size] = '\0';
	i = 0;
	while(i < size)
	{
		dest[i] = line[*index];
		i++;
		*index = *index + 1;
	}
	return (dest);
}

int	get_code(char *line, int *index)
{
	int	code;
	int	sign;
	
	code = 0;
	if (line[*index] == '-')
	{
		sign = -1;
		*index = *index + 1;
	}
	else
		sign = 1;
	while (ft_isdigit(line[*index]))
	{
		code = code * 10 + (line[*index] - '0');
		*index = *index + 1;
	}
	code = code * sign;
	return (code);
}

int	get_label_size(char *line, int	index)
{
	int	size;

	size = 0;
	while (check_valid_label_char(line[index]) && line[index] != '\0')
	{
		size++;
		index++;
	}
	return (size);
}

char	*get_label(char *line, int *index)
{
	char *dest;
	int	i;
	int	size;
	
	i = 0;
	if (line[*index] == LABEL_CHAR)
		*index = *index + 1;
	size = get_label_size(line, *index);
	dest = (char *)malloc(sizeof(char) * size);
	dest[size] = '\0';
	while (i < size)
	{
		dest[i] = line[*index];
		i++;
		*index = *index + 1;
	}
	return (dest);
}

void	get_arguments(char *line, int index, t_command *instruction)
{
	instruction->count_args = 0;
	instruction->args[0] = 0;
	instruction->args[1] = 0;
	instruction->args[2] = 0;
	while (line[index] != '\0' && line[index] != COMMENT_CHAR)
	{
		index = ignore_spaces(line, index);
		if (line[index] == 'r')
		{
			instruction->count_args++;
			index++;
			instruction->args[instruction->count_args] = 1;
			instruction->codage = get_code(line, &index);
		}
		else if (line[index] == '%')
		{
			index++;
			instruction->args[instruction->count_args] = 2;
			if (line[index] == LABEL_CHAR)
				instruction->label = get_label(line, &index);
			else
				instruction->codage = get_code(line, &index);
		}
		else
		{
			instruction->args[instruction->count_args] = 4;
			if (line[index] == LABEL_CHAR)
				instruction->label = get_label(line, &index);
			else
				instruction->codage = get_code(line, &index);
		}
		if (line[index] == SEPARATOR_CHAR)
			index++;
		index = ignore_spaces(line, index);
	}
}

t_command *save_instruction(char *line)
{
	t_command	*instruction;
	int			index;

	index = 0;
	instruction = (t_command *)malloc(sizeof(t_command));
	while(check_valid_label_char(line[index]))
	{
		index++;
	}
	if (line[index] == LABEL_CHAR)
		index++;
	while(line[index] == MTY_SPACE_1 || line[index] == MTY_SPACE_2)
	{
		index++;
	}
	instruction->name = get_instruction_name(line, &index);
	get_arguments(line, index, instruction);
	return (instruction);
}

/*t_label	*save_label(char *line, int size)
{
	t_label *label;
	
	label = (t_label *)malloc(sizeof(t_label));
	label->name = get_label_name(line, size);
	label->instruction = save_instruction(line);
	return (label);
}*/

char *get_first_n_char(char *line, int size)
{
	char *dest;
	int	index;

	dest = (char *)malloc(sizeof(char) * size);
	dest[size] = '\0';
	index = 0;
	while (index < size)
	{
		dest[index] = line[index];
		index++;
	}
	return (dest);
}

// checks the line and reads through the first chars up to ':'
// to see if they are valid LABEL_CHARs then checks the rest of it to see
// if it is a valid statement
bool	check_valid_label(char *line, t_parser *data)
{
	int	index;
	int	size;

	index = 0;
	while (line[index] != LABEL_CHAR)
	{
		if (!check_valid_label_char(line[index]))
			return (false);
		index++;
	}
	size = index;
	if (line[++index] != '\0')
	{
		if (line[index] == MTY_SPACE_1 || line[index] == MTY_SPACE_2)
		{
			if (!check_valid_state(line, index, data))
				exit_usage(3);
		}
		else
			exit_usage(3);
	}
	data->label[data->label_num++] = get_first_n_char(line, size);
	return (true);
}