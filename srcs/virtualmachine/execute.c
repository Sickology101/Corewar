/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:53:52 by igaplich          #+#    #+#             */
/*   Updated: 2023/02/14 18:55:17 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

int	compare_arg_types(t_process *carriage, t_statement *op)
{
	int	i;

	i = 0;
	while (i < op->args_num)
	{
		if (!(carriage->args[i] & op->args[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_args_types(t_data *const data,
		t_process *carriage, t_statement *op)
{
	uint8_t	byte;
	int		type_id;
	int		i;

	if (op->read_types)
	{
		byte = data->arena[(carriage->cur_pos + 1) % MEM_SIZE];
		i = 0;
		while (i < op->args_num)
		{
			type_id = ((byte & (0xC0 >> (i * 2))) >> (6 - i * 2));
			if (type_id == 0)
			{
				carriage->args[i] = 0;
				i++;
				continue ;
			}
			carriage->args[i] = g_arg_code[type_id - 1];
			i++;
		}
	}
	return (compare_arg_types(carriage, op));
}

int	validate_args(t_data *const data, t_process *carriage, t_statement *op)
{
	int		i;
	int		rel_index;
	uint8_t	byte;

	i = 0;
	rel_index = 1;
	if (op->read_types)
		rel_index += 1;
	while (i < op->args_num)
	{
		if (carriage->args[i] == T_REG)
		{
			byte = data->arena[(carriage->cur_pos + rel_index) % MEM_SIZE];
			if (byte < 1 || byte > 16 || carriage->args[i] == 0)
				return (0);
			rel_index++;
		}
		else if (carriage->args[i] == T_DIR)
			rel_index += op->tdir_size;
		else if (carriage->args[i] == T_IND)
			rel_index += IND_SIZE;
		i++;
	}
	return (1);
}

size_t	skip_args(t_process *carriage)
{
	size_t		rel_pos;
	t_statement	*op;
	int			i;

	op = &g_op[carriage->op_id - 1];
	rel_pos = 1 + op->read_types;
	i = 0;
	while (i < op->args_num)
	{
		if (carriage->args[i] == T_REG)
			rel_pos += T_REG;
		else if (carriage->args[i] == T_DIR)
			rel_pos += op->tdir_size;
		else if (carriage->args[i] == T_IND)
			rel_pos += IND_SIZE;
		i++;
	}
	return (rel_pos);
}

void	execute_statement(t_data *const data, t_process *carriage)
{
	t_statement	*op;

	op = NULL;
	if (carriage->op_id - 1 >= 0 && carriage->op_id - 1 < 16)
		op = &g_op[carriage->op_id - 1];
	if (op)
	{
		if (!op->read_types)
			carriage->args[0] = op->args[0];
		if (validate_args_types(data, carriage, op)
			&& validate_args(data, carriage, op))
		{
			op->func(data, carriage);
		}
		else
			carriage->rel_pos = skip_args(carriage);
	}
	else
		carriage->rel_pos = 1;
	move_process(carriage);
}
