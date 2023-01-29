/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/25 20:10:37 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_sti(t_data *const data, t_process *carriage)
{
	int32_t	arg;
	int32_t	reg_value;
	int32_t	rel_pos;

	rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	reg_value = get_arg(data, carriage, &rel_pos, 0);
	arg = get_arg(data, carriage, &rel_pos, 1);
	arg += get_arg(data, carriage, &rel_pos, 2);
	put_reg_value_on_arena(data->arena, (int)reg_value, arg % MEM_SIZE);
	printf("\tWriting %i to index %i\n", (int)reg_value, arg % MEM_SIZE);
	// print_arena(data);
}
