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

	value = 0;
	reg = 0;
	if (carriage->args[0] == DIR_CODE)
	{
		arg = make_dir_to_int(data->arena,
				(carriage->cur_pos + 2) % MEM_SIZE, 4);
		value = arg;
		reg = data->arena[(carriage->cur_pos + 6) % MEM_SIZE];
		reg = calculate_args(REG_CODE, reg);
		if (reg != -1)
			set_next_op(carriage, (carriage->cur_pos + 7) % MEM_SIZE);
	}
	else if (carriage->args[0] == IND_CODE)
	{
		arg = make_ind_to_int(data->arena, (carriage->cur_pos + 2) % MEM_SIZE);
		arg = calculate_args(IND_CODE, arg);
		value = make_dir_to_int(data->arena,
				((int)carriage->cur_pos + arg) % MEM_SIZE, 4);
		reg = data->arena[(carriage->cur_pos + 4) % MEM_SIZE];
		reg = calculate_args(REG_CODE, reg);
		if (reg != -1)
			set_next_op(carriage, (carriage->cur_pos + 5) % MEM_SIZE);
	}
	load_value_to_reg(carriage, value, reg);
	printf("set_ld: value: %i to the register: %i, which is reg[%i]\n", value, reg + 1, reg);
}
