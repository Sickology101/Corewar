/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_statements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:30:08 by marius            #+#    #+#             */
/*   Updated: 2023/02/13 14:18:11 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	handle_1_arg(t_parser *data, char *line, int index)
{
	char	*arg;

	arg = get_arg(line, &index);
	data->line[data->file_size]->arg = (char **)malloc(sizeof(char *));
	if (!check_valid_arg_type(data,
			data->line[data->file_size]->req_arg_type[0], arg, 0))
		exit_usage(4);
	if (data->line[data->file_size]->arg_type[0] == 1)
		check_valid_reg(data, arg, 0);
	else if (data->line[data->file_size]->arg_type[0] == 2)
		check_valid_dir(data, arg, 0);
	else
		check_valid_ind(data, arg, 0);
	index = ignore_spaces(line, index);
	if (line[index] != '\0' && line[index] != COMMENT_CHAR)
		exit_usage(4);
	data->line[data->file_size]->size
		= get_inst_size(data, data->line[data->file_size]->state_code,
			data->line[data->file_size]->arg_type[0]);
}

void	handle_2_arg(t_parser *data, char *line, int index)
{
	char	*arg;

	arg = get_arg(line, &index);
	data->line[data->file_size]->arg = (char **)malloc(sizeof(char *) * 2);
	check_arg(data, arg, 0);
	index = ignore_spaces(line, index);
	if (line[index] == SEPARATOR_CHAR)
		index++;
	else
		exit_usage(4);
	index = ignore_spaces(line, index);
	data->line[data->file_size]->size
		= get_inst_size(data, data->line[data->file_size]->state_code,
			data->line[data->file_size]->arg_type[0]);
	free(arg);
	arg = get_arg(line, &index);
	check_arg(data, arg, 1);
	index = ignore_spaces(line, index);
	if (line[index] != '\0' && line[index] != COMMENT_CHAR)
		exit_usage(4);
	data->line[data->file_size]->size = data->line[data->file_size]->size
		+ get_inst_size(data, data->line[data->file_size]->state_code,
			data->line[data->file_size]->arg_type[1]);
}

void	handle_3_arg(t_parser *data, char *line, int index)
{
	char	*arg;

	arg = get_arg(line, &index);
	data->line[data->file_size]->arg = (char **)malloc(sizeof(char *) * 3);
	check_arg(data, arg, 0);
	index = ignore_spaces(line, index);
	if (line[index] == SEPARATOR_CHAR)
		index++;
	else
		exit_usage(4);
	index = ignore_spaces(line, index);
	data->line[data->file_size]->size = get_inst_size(data,
			data->line[data->file_size]->state_code,
			data->line[data->file_size]->arg_type[0]);
	free(arg);
	arg = get_arg(line, &index);
	check_arg(data, arg, 1);
	index = ignore_spaces(line, index);
	if (line[index] == SEPARATOR_CHAR)
		index++;
	else
		exit_usage(4);
	handle_3_arg_2(data, line, index);
}

void	get_statement(t_parser *data, char *line, int index)
{
	get_name(data, line, &index);
	if (!check_valid_statement_name(data->line[data->file_size]->statement,
			data))
		exit_usage(3);
	data->line[data->file_size]->arg_num
		= (long long *)malloc(sizeof(long long)
			* data->line[data->file_size]->req_arg_num);
	index = ignore_spaces(line, index);
	data->line[data->file_size]->dir_loc[0] = 0;
	data->line[data->file_size]->dir_loc[1] = 0;
	data->line[data->file_size]->dir_loc[2] = 0;
	if (line[index] == '\0')
		exit_usage(4);
	if (data->line[data->file_size]->req_arg_num == 1)
		handle_1_arg(data, line, index);
	else if (data->line[data->file_size]->req_arg_num == 2)
		handle_2_arg(data, line, index);
	else
		handle_3_arg(data, line, index);
	handle_arg_code(data);
	data->line[data->file_size]->size++;
}
