/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:08 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/30 17:25:29 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

/*
** set_fork makes a copy of the process in question,
** and puts it on the arena in the place that is set in the argument.
** Differs from fork by number of cycles and doesn't need IDX modulo truncation.
*/
void	set_lfork(t_data *const data, t_process *carriage)
{
	int			arg;
	t_process	*copy;

	carriage->rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	arg = get_arg(data, carriage, &carriage->rel_pos, 0);
	printf("\n\n\tlfork current position: %zu\n", carriage->cur_pos % MEM_SIZE);
	printf("\tdump : %i\n\n", data->dump_cycles);
	copy_process(data, carriage, (carriage->cur_pos + arg) % MEM_SIZE);
	copy = data->process_tail;
	put_process_on_arena(data, copy, carriage->cur_pos % MEM_SIZE,
		(carriage->cur_pos + 2) % MEM_SIZE);
	printf("\tset_lfork: Making a LONG fork at arena[%zu]\n",
		carriage->cur_pos + arg % MEM_SIZE);
	printf("\ncycle: %i\n", data->counter.total_cycles);
}
