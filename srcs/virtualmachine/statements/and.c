/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:01 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/27 19:41:26 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_and(t_data *const data, t_process *carr)
{
	int	arg1;
	int	arg2;
	int	reg_index;
	int	rel_pos;

	rel_pos = 1 + g_op[carr->op_id - 1].read_types;
	arg1 = get_arg(data, carr, &rel_pos, 0);
	arg2 = get_arg(data, carr, &rel_pos, 1);
	reg_index = data->arena[carr->cur_pos + rel_pos];
	carr->reg[reg_index] = (arg1 & arg2);
	set_carry(carr, reg_index);
	set_next_op(carr, (carr->cur_pos + rel_pos) % MEM_SIZE);
}
