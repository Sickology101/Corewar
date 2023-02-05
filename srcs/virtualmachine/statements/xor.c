/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/25 20:10:42 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_xor(t_data *const data, t_process *carr)
{	
	int	arg1;
	int	arg2;
	int	reg_index;
	int	idx;

	idx = IDX_MOD;
	carr->rel_pos = 1 + g_op[carr->op_id - 1].read_types;
	arg1 = get_arg(data, carr, 0, idx);
	arg2 = get_arg(data, carr, 1, idx);
	reg_index = data->arena[carr->cur_pos + carr->rel_pos] - 1;
	carr->rel_pos += T_REG;
	carr->reg[reg_index] = (arg1 ^ arg2);
	set_carry(carr, reg_index);
}
