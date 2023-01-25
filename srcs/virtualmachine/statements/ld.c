/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/25 18:35:01 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	load_value_to_reg(t_process *carriage, int value, int reg)
{
	if (!value)
		carriage->carry = 1;
	else
		carriage->carry = 0;
	// write value to registry[carriage->args[1]], so registry[reg];
}

void	set_ld(t_data *const data, t_process *carriage)
{
	int		arg;
	int8_t	reg;
	int		value;

	value = 0;
	reg = 0;
	if (carriage->args[0] == DIR_CODE)
	{
		arg = make_dir_to_int(data->arena, carriage->cur_pos);
		value = arg;
		reg = data->arena[carriage->cur_pos + 6];
		set_next_op(carriage, carriage->cur_pos + 7);
	}
	else if (carriage->args[0] == IND_CODE)
	{
		arg = make_ind_to_int(data->arena, carriage->cur_pos + 1);
		arg = calculate_args(IND_CODE, arg);
		value = make_dir_to_int(data->arena, (int)carriage->cur_pos + arg);
		reg = data->arena[carriage->cur_pos + 4];
		set_next_op(carriage, carriage->cur_pos + 5);
	}
	load_value_to_reg(carriage, value, reg);
	printf("set_ld: value: %i to the register: %i\n", value, reg);
}

/*
	in theory ld-statement will be done when we write the value to the registry.
*/
