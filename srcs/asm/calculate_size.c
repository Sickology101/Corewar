/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:20:20 by marius            #+#    #+#             */
/*   Updated: 2023/01/28 03:51:12 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*int	get_state_type(char *state, char **statements)
{
	int	index;
	
	index = 0;
	while (index < 16)
	{
		if (!ft_strcmp(state, statements[index]))
			return (index + 1);
	}
	return (0);
}

int	calc_arg_size(char *line, int index, int dir_size)
{
	int size;

	size = 0;
	while (line[index] != '\0')
	{
		index = ignore_spaces(line, index);
		if (line[index] == 'r')
			size++;
		else if (line[index] == '%')
			size = size + dir_size;
		else
			size = size + 2;
		while (line[index] != SEPARATOR_CHAR && line[index] != '\0')
		{
			index++;
		}
	}
	return (size);
}

int	calculate_size(char *line, t_parser *data)
{
	int	type;
	int size;
	int	index;

	index = 0;
	if (line[index] != MTY_SPACE_1 && line[index] != MTY_SPACE_2)
	{
		while(line[index] != LABEL_CHAR)
		{
			index++;
		}
		index++;
	}
	index = ignore_spaces(line, index);
	type = get_state_type(get_syntax_name(line, &index), data->s);
	if (type == 1 || type == 9 || type == 12 || type == 15)
		size = 1;
	else
		size = 2;
	if (type < 9 || type == 13 || type == 16)
		size = size + calc_arg_size(line, index, 4);
	else
		size = size + calc_arg_size(line, index, 2);
	return (size);
}*/
