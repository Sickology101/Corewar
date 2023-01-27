/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:53:52 by igaplich          #+#    #+#             */
/*   Updated: 2023/01/27 19:33:20 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

int	validate_args_types(t_data *const data,
		t_process *carriage, t_statement *op)
{
	uint8_t	byte;
	int		i;

	byte = data->arena[carriage->cur_pos + 1 % MEM_SIZE];
	i = 0;
	while (i < op->args_num)
	{
		carriage->args[i] = (byte & (0xc0 >> i * 2)) >> (6 - i * 2);
		if (!(carriage->args[i] & op->args[i])) 		//TODO: CHECK THAT IT ACTUALLY WORKS
		{
			printf("arg types wrong\n");
			return (0);
		}
		i++;
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
		if (carriage->args[i] == REG_CODE)
		{
			byte = data->arena[carriage->cur_pos + rel_index];
			if (byte < 1 || byte > 16)
				return (0);
			rel_index++;
		}
		else if (carriage->args[i] == DIR_CODE)
			rel_index += op->tdir_size;
		else if (carriage->args[i] == IND_CODE)
			rel_index += IND_SIZE;
		i++;
	}
	return (1);
}

void	execute_statement(t_data *const data, t_process *carriage)
{
	t_statement	*op;

	op = &g_op[data->arena[carriage->cur_pos] - 1];
	if (!op->read_types || validate_args_types(data, carriage, op))
	{
		printf("Arg types are ok\n");
		if (validate_args(data, carriage, op))
		{
			op->func(data, carriage);
			printf("args are also ok\n");
		}
		else
			printf("args are not ok\n");
	}
}
