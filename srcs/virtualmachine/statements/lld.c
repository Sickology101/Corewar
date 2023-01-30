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
	int8_t	reg;
	int		value;
	int		rel_pos;

	rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	value = get_arg(data, carriage, &rel_pos, 0);
	reg = get_arg(data, carriage, &rel_pos, 1);
	if (reg != -1)
		set_next_op(carriage, (carriage->cur_pos + rel_pos) % MEM_SIZE);
	load_value_to_reg(carriage, value, reg);
	printf("set_lld: value: %i to the register: %i, which is reg[%i]\n", value, reg + 1, reg);
	set_next_op(carriage, (carriage->cur_pos + rel_pos) % MEM_SIZE);
}
