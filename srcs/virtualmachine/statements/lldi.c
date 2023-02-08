/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/02/08 18:57:06 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_lldi(t_data *const data, t_process *carr)
{	
	int	addr;
	int	reg_id;
	int	idx;
	int	value;

	idx = 0;
	carr->rel_pos = 1 + g_op[carr->op_id - 1].read_types;
	addr = get_arg(data, carr, 0, idx);
	addr += get_arg(data, carr, 1, idx);
	value = read_4_bytes(data->arena, carr->cur_pos + addr);
	reg_id = data->arena[(carr->cur_pos + carr->rel_pos) % MEM_SIZE] - 1;
	carr->rel_pos += T_REG;
	load_value_to_reg(carr, value, reg_id);
}
