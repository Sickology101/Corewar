/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:53:52 by igaplich          #+#    #+#             */
/*   Updated: 2023/02/02 15:42:28 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

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
		i = 0;
		while (i < op->args_num)
		{
			if (!(carriage->args[i] & op->args[i]))
			{
				printf("\targ types wrong\n");
				return (0);
			}
			i++;
		}
	}
	return (1);
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
			if (byte < 1 || byte > 16)
			{
				printf("\targs are not ok\n");
				return (0);
			}
			rel_index++;
		}
		else if (carriage->args[i] == T_DIR)
			rel_index += op->tdir_size;
		else if (carriage->args[i] == T_IND)
			rel_index += IND_SIZE;
		else if (carriage->args[i] == 0)
			return(0);
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
	if (data->arena[carriage->cur_pos % MEM_SIZE] - 1 >= 0 && data->arena[carriage->cur_pos % MEM_SIZE] - 1 <= 15)
		op = &g_op[data->arena[carriage->cur_pos % MEM_SIZE] - 1];
	if (op)
	{
		if (carriage->unique_id == 4)
		{
			printf("ID4 %s %d %d\n", op->name, data->counter.cycles_total, carriage->carry);
		}
		printf("------------------------------\n");
		printf("\n%s at position %zu at cycle %d\n", g_op[carriage->op_id - 1].name, carriage->cur_pos, data->counter.cycles_total);
		if (!op->read_types)
			carriage->args[0] = op->args[0];
		if (validate_args_types(data, carriage, op) && validate_args(data, carriage, op))
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
