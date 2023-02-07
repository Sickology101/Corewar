/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_statements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:50:37 by macbook           #+#    #+#             */
/*   Updated: 2023/01/30 17:17:19 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	set_statement_codes(t_data *const data, t_process *carriage)
{
	carriage->op_id = data->arena[carriage->cur_pos];
	if (data->arena[carriage->cur_pos] >= 1 && data->arena[carriage->cur_pos] <= 16)
		carriage->cycles_before_exec = g_op[carriage->op_id - 1].cycles_num;
}

void	move_process(t_process *carriage)
{
	int	i;

	carriage->cur_pos = (carriage->cur_pos + carriage->rel_pos) % MEM_SIZE;
	carriage->rel_pos = 0;
	i = 0;
	while (carriage->args[i] < 3)
	{
		carriage->args[i] = 0;
		i++;
	}
}

void	perform_cycle(t_data *const data)
{
	t_process	*carriage;

	data->counter.cycles_total++;
	data->counter.cycles_after_check++;
	carriage = data->process_head;
	while (carriage)
	{
		if (carriage->cycles_before_exec == 0)
			set_statement_codes(data, carriage);
		if (carriage->cycles_before_exec > 0)
			carriage->cycles_before_exec--;
		if (carriage->cycles_before_exec == 0)
			execute_statement(data, carriage);
		carriage = carriage->next;
	}
}
