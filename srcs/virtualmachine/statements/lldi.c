/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/02/13 19:58:55 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_lldi(t_data *const data, t_process *carr)
{	
	int	addr1;
	int	addr2;
	int	reg_id;
	int	address;
	int	value;

	carr->rel_pos = 1 + g_op[carr->op_id - 1].read_types;
	addr1 = get_arg(data, carr, 0, IDX_MOD);
	addr2 = get_arg(data, carr, 1, IDX_MOD);
	address = (carr->cur_pos + (addr1 + addr2)) % MEM_SIZE;
	if (address < 0)
		address = MEM_SIZE + address;
	value = read_4_bytes(data->arena, address);
	reg_id = data->arena[(carr->cur_pos + carr->rel_pos) % MEM_SIZE] - 1;
	carr->rel_pos += T_REG;
	load_value_to_reg(carr, value, reg_id);
}
