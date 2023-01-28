/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/26 20:49:30 by mtissari         ###   ########.fr       */
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
*/
void	set_ld(t_data *const data, t_process *carriage)
{
	int		arg;
	int8_t	reg;
	int		value;
	int		rel_pos;

	rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	value = 0;
	reg = 0;
	arg = get_arg(data, carriage, &rel_pos, 0);
	value = arg;
	reg = get_arg(data, carriage, &rel_pos, 1);
	if (reg != -1)
		set_next_op(carriage, (carriage->cur_pos + rel_pos) % MEM_SIZE);
	load_value_to_reg(carriage, value, reg);
	printf("set_ld: value: %i to the register: %i, which is reg[%i]\n", value, reg + 1, reg);
}
