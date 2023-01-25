/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:03 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/25 20:04:17 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	place_process_on_arena(t_data *const data,
		t_process *copy, int start, int end)
{
	int	i;

	i = 0;
	while (start <= end)
	{
		data->arena[copy->cur_pos + i] = data->arena[start];
		printf("new: %0.2x\n", data->arena[copy->cur_pos + i]);
		start++;
		i++;
	}
}

void	set_fork(t_data *const data, t_process *carriage)
{
	int			arg;
	t_process	*copy;

	arg = make_dir_to_int(data->arena, carriage->cur_pos);
	arg = calculate_args(DIR_CODE, arg) % IDX_MOD;
	printf("\n\n\tcurrent position: %zu\n", carriage->cur_pos);
	printf("\tdump : %i\n\n", data->dump_cycles);
	copy_process(data, carriage, carriage->cur_pos + arg);
	copy = data->process_tail;
	place_process_on_arena(data, copy, carriage->cur_pos, carriage->cur_pos + 2);
	printf("\tset_fork: Making a fork at arena[%zu]\n", carriage->cur_pos + arg);
	printf("\ncycle: %i\n", data->counter.total_cycles);
	set_next_op(carriage, carriage->cur_pos + 3);
}
