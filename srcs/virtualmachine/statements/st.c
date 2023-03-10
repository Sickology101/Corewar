/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/02/14 17:15:07 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

/*
** set_st writes the value of the registry that matches the first argument to
** the location of the second argument.
** If the second argument is T_REG, the value will be written to the registry
** that matches the second argument.
** If the second argument is T_IND, the value will be written on the arena to
** the place the second argument suggests.
*/
void	set_st(t_data *const data, t_process *carr)
{
	int		address;
	int		reg_id;
	int32_t	reg_value;
	int		idx;

	idx = IDX_MOD;
	carr->rel_pos = 1 + g_op[carr->op_id - 1].read_types;
	reg_id = data->arena[(carr->cur_pos + carr->rel_pos) % MEM_SIZE] - 1;
	carr->rel_pos += T_REG;
	reg_value = carr->reg[reg_id];
	if (carr->args[1] == T_IND)
	{
		address = read_bytes(data->arena,
				carr->cur_pos + carr->rel_pos, IND_SIZE);
		carr->rel_pos += IND_SIZE;
		put_reg_value_on_arena(data->arena, (int)reg_value,
			carr->cur_pos + (address % idx), DIR_SIZE);
	}
	else if (carr->args[1] == T_REG)
	{
		address = data->arena[(carr->cur_pos + carr->rel_pos) % MEM_SIZE] - 1;
		carr->reg[address] = reg_value;
		carr->rel_pos += T_REG;
	}
}
