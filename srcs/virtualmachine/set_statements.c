/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_statements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:50:37 by macbook           #+#    #+#             */
/*   Updated: 2023/01/24 20:49:05 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	set_statement_codes(t_data *const data, t_process *carriage)
{
	if (carriage->cycles_before_exec <= 0)
	{
		carriage->op_id = data->arena[carriage->cur_pos];
		if (data->arena[carriage->cur_pos] >= 1 && data->arena[carriage->cur_pos] <= 16)
			carriage->cycles_before_exec = g_op[carriage->op_id - 1].cycles_num;
		else
			carriage->cycles_before_exec = 0;
		printf("\n%s -> %02x cycles %d\n", carriage->player->name, carriage->op_id, carriage->cycles_before_exec);
	}
}

void	move_process(t_process *carriage)
{
	if (carriage->cycles_before_exec <= 0)
	{
		if (carriage->cur_pos == 4095)
			carriage->cur_pos = 0;
		else
			carriage->cur_pos++;
	}
}

void	perform_cycle(t_data *const data)
{
	t_process	*carriage;

	carriage = data->process_head;
	while (carriage)
	{
		set_statement_codes(data, carriage);
		if (carriage->cycles_before_exec > 0)
			carriage->cycles_before_exec--;
		if (carriage->cycles_before_exec == 0
			&& carriage->op_id >= 1 && carriage->op_id <= 16)
			execute_statement(data, carriage);
		move_process(carriage);
		carriage = carriage->next;
	}
}
