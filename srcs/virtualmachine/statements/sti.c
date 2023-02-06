/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/30 17:24:21 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_sti(t_data *const data, t_process *carriage)
{
	int32_t	arg;
	int32_t	reg_value;
	int		idx;

	idx = 0;
	carriage->rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	reg_value = get_arg(data, carriage, 0, idx);
	arg = get_arg(data, carriage, 1, idx);
	arg += get_arg(data, carriage, 2, idx);
	arg = arg % IDX_MOD;
	put_reg_value_on_arena(data->arena, (int)reg_value, carriage->cur_pos + arg, DIR_SIZE);
	printf("\tWriting %i to index %i carr id = %zu\n", (int)reg_value, arg, carriage->unique_id);
	// print_arena_term(data);
}
