/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:06 by mtissari          #+#    #+#             */
/*   Updated: 2023/02/08 15:17:00 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_ldi(t_data *const data, t_process *carr)
{	
	int	addr;
	int	reg_id;
	int idx;

	idx = 0;
	carr->rel_pos = 1 + g_op[carr->op_id - 1].read_types;
	addr = get_arg(data, carr, 0, idx);
	addr += get_arg(data, carr, 1, idx);
	reg_id = data->arena[carr->cur_pos + carr->rel_pos] - 1;
	carr->rel_pos += T_REG;
	carr->reg[reg_id] = read_4_bytes(data->arena, carr->cur_pos + (addr % IDX_MOD));
	printf("ldi: reg[%i]: %i\n", reg_id + 1, carr->reg[reg_id]);
}
