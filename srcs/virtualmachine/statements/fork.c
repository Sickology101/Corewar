/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:03 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/26 20:19:01 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

/*
** set_fork makes a copy of the process in question,
** and puts it on the arena in the place that is set in the argument.
*/
void	set_fork(t_data *const data, t_process *carriage)
{
	int			address;
	t_process	*copy;
	int			idx;

	idx = IDX_MOD;
	carriage->rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	address = get_arg(data, carriage, 0, idx);
	copy = copy_process(data, carriage, address % idx);
	if (data->process_head)
		copy->next = data->process_head;
	data->process_head = copy;
}
