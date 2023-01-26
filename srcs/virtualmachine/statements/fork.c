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
	int			arg;
	t_process	*copy;

	arg = make_dir_to_int(data->arena, (carriage->cur_pos + 1) % MEM_SIZE, 2);
	arg = calculate_args(DIR_CODE, arg) % IDX_MOD;
	printf("\n\nfork\tcurrent position: %zu\n", carriage->cur_pos);
	printf("\tdump : %i\n\n", data->dump_cycles);
	copy_process(data, carriage, (carriage->cur_pos + arg) % MEM_SIZE);
	copy = data->process_tail;
	put_process_on_arena(data, copy, carriage->cur_pos,
		(carriage->cur_pos + 2) % MEM_SIZE);
	printf("\tset_fork: Making a fork at arena[%zu]\n",
		(carriage->cur_pos + arg) % MEM_SIZE);
	printf("\ncycle: %i\n", data->counter.total_cycles);
	set_next_op(carriage, (carriage->cur_pos + 3) % MEM_SIZE);
}
