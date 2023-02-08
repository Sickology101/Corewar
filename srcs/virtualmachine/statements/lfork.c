/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:08 by mtissari          #+#    #+#             */
/*   Updated: 2023/02/08 19:19:27 by mtissari         ###   ########.fr       */
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
	int			idx;

	idx = IDX_MOD;
	carriage->rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	arg = get_arg(data, carriage, 0, idx);
	copy = copy_process(data, carriage, arg);
	copy->next = data->process_head;
	data->process_head = copy;
}
