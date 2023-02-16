/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/02/08 19:25:27 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_or(t_data *const data, t_process *carriage)
{
	int	arg1;
	int	arg2;
	int	reg_id;
	int	idx;

	idx = IDX_MOD;
	carriage->rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	arg1 = get_arg(data, carriage, 0, idx);
	arg2 = get_arg(data, carriage, 1, idx);
	reg_id = data->arena[(carriage->cur_pos + carriage->rel_pos)
		% MEM_SIZE] - 1;
	carriage->rel_pos += T_REG;
	load_value_to_reg(carriage, arg1 | arg2, reg_id);
}
