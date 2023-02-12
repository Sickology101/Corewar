/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/02/08 13:33:00 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	load_value_to_reg(t_process *carriage, int value, int reg_num)
{
	if (!value)
		carriage->carry = 1;
	else
		carriage->carry = 0;
	carriage->reg[reg_num] = value;
}

/*
** set_ld loads the argument value to the given registry,
** and changes the value of carry.
** if registry index is wrong, we just skip the statement with it's arguments.
*/
void	set_ld(t_data *const data, t_process *carriage)
{
	int8_t	reg_id;
	int		idx;
	int		value;

	idx = IDX_MOD;
	carriage->rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	value = get_arg(data, carriage, 0, idx);
	reg_id = data->arena[(carriage->cur_pos + carriage->rel_pos)
		% MEM_SIZE] - 1;
	carriage->rel_pos += T_REG;
	load_value_to_reg(carriage, value, reg_id);
}
