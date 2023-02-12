/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/02/08 15:49:52 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

/*
** set_sub sets the value of the third argument as argument1 - argument2.
*/
void	set_sub(t_data *const data, t_process *carr)
{
	int	arg1;
	int	arg2;
	int	reg_id;
	int	idx;

	idx = IDX_MOD;
	carr->rel_pos = 1 + g_op[carr->op_id - 1].read_types;
	arg1 = get_arg(data, carr, 0, idx);
	arg2 = get_arg(data, carr, 1, idx);
	reg_id = data->arena[carr->cur_pos + carr->rel_pos] - 1;
	carr->rel_pos += T_REG;
	load_value_to_reg(carr, arg1 - arg2, reg_id);
	set_carry(carr, carr->reg[reg_id]);
}
