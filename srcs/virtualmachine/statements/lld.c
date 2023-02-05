/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/30 17:24:59 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_lld(t_data *const data, t_process *carriage)
{
	int8_t	reg_id;
	int		value;
	int		idx;

	idx = 0;
	carriage->rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	value = get_arg(data, carriage, 0, idx);
	reg_id = data->arena[(carriage->cur_pos + carriage->rel_pos) % MEM_SIZE] - 1;
	carriage->rel_pos += T_REG;
	load_value_to_reg(carriage, value, reg_id);
	printf("set_lld: value: %i to the register: %i, which is reg[%i]\n", value, reg_id + 1, reg_id);
}
