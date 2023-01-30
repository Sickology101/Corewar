/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/30 17:41:38 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_lldi(t_data *const data, t_process *carr)
{	
	int	addr;
	int	reg_id;
	int	rel_pos;

	rel_pos = 1 + g_op[carr->op_id - 1].read_types;
	addr = get_arg(data, carr, &rel_pos, 0);
	addr += get_arg(data, carr, &rel_pos, 1);
	reg_id = data->arena[carr->cur_pos + rel_pos] - 1;
	carr->reg[reg_id] = data->arena[carr->cur_pos + addr];
	set_next_op(carr, (carr->cur_pos + rel_pos) % MEM_SIZE);
}
