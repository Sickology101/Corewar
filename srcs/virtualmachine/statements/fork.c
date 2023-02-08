/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:03 by mtissari          #+#    #+#             */
/*   Updated: 2023/02/08 18:02:48 by mtissari         ###   ########.fr       */
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
	printf("\t\t\t|-|=-|+| copied process location: %zu |-|=-|+| carriage_id: %zu, from carriage: %zu\n", copy->cur_pos, copy->unique_id, carriage->unique_id);
	copy->next = data->process_head;
	data->process_head = copy;
}
