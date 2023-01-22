/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:53:52 by igaplich          #+#    #+#             */
/*   Updated: 2023/01/22 17:53:53 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

int	validate_args_types(t_data *const data, t_process *carriage, t_statement *op)
{
	uint8_t byte;
	int i;

	byte = data->arena[carriage->cur_pos + 1 % 4098];
	i = 0;
	while (i < op->args_num)
	{
		carriage->args[i] = (byte & (0xc0 >> i * 2)) >> (6 - i * 2);
		if (!(carriage->args[i] & op->args[i]))
			return (0);
		i++;
	}
	return (1);
}


void	execute_statement(t_data *const data, t_process *carriage)
{
	t_statement *operation;

	operation = &g_op[carriage->op_id - 1];
	if (validate_args_types(data, carriage, operation) || !operation->read_types)
	{
		printf("arg types ok\n");
		// if (validate_args(data, carriage))
			operation->func(data, carriage);
	}
	else
		printf("arg types wrong\n");
}