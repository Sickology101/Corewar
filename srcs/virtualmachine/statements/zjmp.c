/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/26 20:19:49 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

/*
** set_zjmp relocates the process on the arena to the place the argument says,
** but only if the carry is 1. Otherwise we carry on as usual.
*/
void	set_zjmp(t_data *const data, t_process *carriage)
{
	int	arg;
	int	rel_pos;

	rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	arg = get_arg(data, carriage, &rel_pos, 0);
	carriage->last_live = data->counter.total_cycles;
	if (carriage->carry)
		set_next_op(carriage, (carriage->cur_pos + arg) % MEM_SIZE);
	else
		set_next_op(carriage, (carriage->cur_pos + 3) % MEM_SIZE);
}
