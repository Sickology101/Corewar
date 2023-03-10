/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:05:56 by mtissari          #+#    #+#             */
/*   Updated: 2023/02/14 17:10:30 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

/*
** set_sub sets the value of the third argument as argument1 + argument2.
*/
void	set_add(t_data *const data, t_process *carr)
{
	int	arg1;
	int	arg2;
	int	reg_id;
	int	idx;

	idx = 0;
	carr->rel_pos = 1 + g_op[carr->op_id - 1].read_types;
	arg1 = get_arg(data, carr, 0, idx);
	arg2 = get_arg(data, carr, 1, idx);
	reg_id = data->arena[(carr->cur_pos + carr->rel_pos) % MEM_SIZE] - 1;
	carr->rel_pos += T_REG;
	load_value_to_reg(carr, arg1 + arg2, reg_id);
}
