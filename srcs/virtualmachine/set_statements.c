/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_statements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:50:37 by macbook           #+#    #+#             */
/*   Updated: 2023/01/18 21:50:40 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	reduce_cycle_bf_execution(t_data *const data, t_process *carriage)
{
	if (carriage->cycles_before_exec >= 0)
		carriage->cycles_before_exec--;
}

void	set_statement_codes(t_data *const data, t_process *carriage)
{
	if (carriage->cycles_before_exec == 0)
	{
		if (data->arena[carriage->cur_pos] >= 1 && data->arena[carriage->cur_pos] <= 16)
		{
			carriage->operation_code = data->arena[carriage->cur_pos];
			// Here we should also set amount of cycles for operation, that we have read
			// but if arena[i] < 1 or > 16, amount of cycles stays 0
		}
		else
			carriage->cycles_before_exec = 0;
		printf("\n%s -> %#04x\n", carriage->player->name, carriage->operation_code);
	}
}

void	perform_cycle(t_data *const data)
{
	t_process	*carriage;

	carriage = data->process_head;
	while (carriage)
	{
		set_statement_codes(data, carriage);
		reduce_cycle_bf_execution(data, carriage);
		// execute_statements_and_move_processes();
		carriage = carriage->next;
	}
}