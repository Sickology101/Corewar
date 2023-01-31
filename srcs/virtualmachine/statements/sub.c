/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/30 17:41:48 by mtissari         ###   ########.fr       */
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

	print_arena(data);
	carr->rel_pos = 1 + g_op[carr->op_id - 1].read_types;
	arg1 = get_arg(data, carr, &carr->rel_pos, 0);
	arg2 = get_arg(data, carr, &carr->rel_pos, 1);
	reg_id = data->arena[carr->cur_pos + carr->rel_pos] - 1;
	carr->rel_pos += T_REG;
	carr->reg[reg_id] = arg1 - arg2;
	set_carry(carr, reg_id);
	printf("arena now [%.2x] and next [%.2x]", data->arena[carr->cur_pos], data->arena[(carr->cur_pos + carr->rel_pos) % MEM_SIZE]);
}
