/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_statements4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:40:18 by marius            #+#    #+#             */
/*   Updated: 2023/02/05 16:08:32 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	check_arg(t_parser *data, char *arg, int flag)
{
	if (!check_valid_arg_type(data,
			data->line[data->file_size]->req_arg_type[flag], arg, flag))
		exit_usage(4);
	if (data->line[data->file_size]->arg_type[flag] == 1)
		check_valid_reg(data, arg, flag);
	else if (data->line[data->file_size]->arg_type[flag] == 2)
		check_valid_dir(data, arg, flag);
	else
		check_valid_ind(data, arg, flag);
}

void	handle_3_arg_2(t_parser *data, char *line, int index)
{
	char	*arg;

	index = ignore_spaces(line, index);
	data->line[data->file_size]->size = data->line[data->file_size]->size
		+ get_inst_size(data, data->line[data->file_size]->state_code,
			data->line[data->file_size]->arg_type[1]);
	arg = get_arg(line, &index);
	check_arg(data, arg, 2);
	index = ignore_spaces(line, index);
	if (line[index] != '\0' && line[index] != COMMENT_CHAR)
		exit_usage(4);
	data->line[data->file_size]->size = data->line[data->file_size]->size
		+ get_inst_size(data, data->line[data->file_size]->state_code,
			data->line[data->file_size]->arg_type[2]);
}

void	handle_arg_code(t_parser *data)
{
	if (data->line[data->file_size]->state_code == 1
		|| data->line[data->file_size]->state_code == 9
		|| data->line[data->file_size]->state_code == 12
		|| data->line[data->file_size]->state_code == 15)
		data->line[data->file_size]->arg_code_req = false;
	else
	{
		gen_arg_code(data);
		data->line[data->file_size]->arg_code_req = true;
		data->line[data->file_size]->size++;
	}
}
