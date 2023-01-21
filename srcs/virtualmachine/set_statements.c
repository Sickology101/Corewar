/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_statements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:50:37 by macbook           #+#    #+#             */
/*   Updated: 2023/01/21 15:52:03 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	reduce_cycle_bf_execution(t_process *carriage)
{
	if (carriage->cycles_before_exec >= 0)
		carriage->cycles_before_exec--;
}

void	set_statement_codes(t_data *const data, t_process *carriage)
{
	if (carriage->cycles_before_exec <= 0)
	{
		carriage->operation_code = data->arena[carriage->cur_pos];
		if (data->arena[carriage->cur_pos] >= 1 && data->arena[carriage->cur_pos] <= 16)
			carriage->cycles_before_exec = action[carriage->operation_code - 1].cycles_num;
		else
			carriage->cycles_before_exec = 0;
		printf("\n%s -> %02x cycles %d\n", carriage->player->name, carriage->operation_code, carriage->cycles_before_exec);
	}
}

void	move_process(t_process *carriage)
{
	if (carriage->cycles_before_exec <= 0) // unsure of this!
	{
		if (carriage->cur_pos == 4095)
			carriage->cur_pos = 0;
		else
			carriage->cur_pos++;
	}
	//else  	//there is no "else", but just put this here as a note
		// just wait until the cycles_before_exec is 0
		// so don't go to the next operation yet
}

void	perform_cycle(t_data *const data)
{
	t_process	*carriage;

	carriage = data->process_head;
	while (carriage)
	{
		set_statement_codes(data, carriage);
		reduce_cycle_bf_execution(carriage);
	//	execute_statement(data, carriage);
		move_process(carriage);
		carriage = carriage->next;
	}
}
