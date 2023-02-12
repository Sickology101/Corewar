/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_statements2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:13:22 by marius            #+#    #+#             */
/*   Updated: 2023/02/12 13:45:49 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

t_statements	g_operations[17]
	= {{"live", 1, {T_DIR, 0, 0}},
{"ld", 2, {T_DIR + T_IND, T_REG, 0}},
{"st", 2, {T_REG, T_REG + T_IND}},
{"add", 3, {T_REG, T_REG, T_REG}},
{"sub", 3, {T_REG, T_REG, T_REG}},
{"and", 3, {T_REG + T_DIR + T_IND, T_REG + T_DIR + T_IND, T_REG}},
{"or", 3, {T_REG + T_DIR + T_IND, T_REG + T_DIR + T_IND, T_REG}},
{"xor", 3, {T_REG + T_DIR + T_IND, T_REG + T_DIR + T_IND, T_REG}},
{"zjmp", 1, {T_DIR, 0, 0}},
{"ldi", 3, {T_REG + T_DIR + T_IND, T_REG + T_DIR, T_REG}},
{"sti", 3, {T_REG, T_REG + T_DIR + T_IND, T_REG + T_DIR}},
{"fork", 1, {T_DIR, 0, 0}},
{"lld", 2, {T_DIR + T_IND, T_REG, 0}},
{"lldi", 3, {T_REG + T_DIR + T_IND, T_REG + T_DIR, T_REG}},
{"lfork", 1, {T_DIR, 0, 0}},
{"aff", 1, {T_REG, 0, 0}},
{NULL, 0, {0, 0, 0}}
};

int	get_name_size(char *line, int index)
{
	int	size;

	size = 0;
	while (line[index] != MTY_SPACE_1 && line[index] != MTY_SPACE_2
		&& line[index] != '\0' && line[index] != SEPARATOR_CHAR)
	{
		size++;
		index++;
	}
	return (size);
}

void	get_name(t_parser *data, char *line, int *index)
{
	int	size;
	int	i;

	size = get_name_size(line, *index);
	data->line[data->file_size]->statement
		= (char *)malloc(sizeof(char) * size);
	data->line[data->file_size]->statement[size] = '\0';
	i = 0;
	while (i < size)
	{
		data->line[data->file_size]->statement[i] = line[*index];
		i++;
		*index = *index + 1;
	}
}

bool	check_valid_statement_name(char *str, t_parser *data)
{
	int	index;

	index = 0;
	while (index < 16)
	{
		if (!ft_strcmp(str, g_operations[index].name))
		{
			data->line[data->file_size]->state_code = index + 1;
			data->line[data->file_size]->req_arg_num
				= g_operations[index].arg_num;
			data->line[data->file_size]->req_arg_type[0]
				= g_operations[index].arg[0];
			data->line[data->file_size]->req_arg_type[1]
				= g_operations[index].arg[1];
			data->line[data->file_size]->req_arg_type[2]
				= g_operations[index].arg[2];
			return (true);
		}
		index++;
	}
	return (false);
}

char	*get_arg(char *line, int *index)
{
	char	*dest;
	int		size;
	int		i;

	size = get_name_size(line, *index);
	if (line[*index + size - 1] == SEPARATOR_CHAR)
		size--;
	i = 0;
	dest = ft_strnew(size);
	while (i < size)
	{
		dest[i] = line[*index];
		i++;
		*index = *index + 1;
	}
	return (dest);
}

bool	check_valid_arg_type(t_parser *data, int flag, char *arg, int index)
{
	int	arg_type;

	if (arg[0] == 'r')
		data->line[data->file_size]->arg_type[index] = 1;
	else if (arg[0] == '%')
		data->line[data->file_size]->arg_type[index] = 2;
	else
		data->line[data->file_size]->arg_type[index] = 4;
	arg_type = data->line[data->file_size]->arg_type[index];
	if (arg_type == flag)
		return (true);
	if (flag == 3)
		if (arg_type == 1 || arg_type == 2)
			return (true);
	if (flag == 5)
		if (arg_type == 1 || arg_type == 4)
			return (true);
	if (flag == 6)
		if (arg_type == 2 || arg_type == 4)
			return (true);
	if (flag == 7)
		return (true);
	return (false);
}
