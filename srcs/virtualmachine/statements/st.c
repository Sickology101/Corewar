/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/27 17:07:23 by mtissari         ###   ########.fr       */
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
	int		arg;
	int32_t	reg_value;
	int		rel_pos;

	rel_pos = 1 + g_op[carr->op_id - 1].read_types;
	reg_value = get_arg(data, carr, &rel_pos, 0) - 1;
	if (carr->args[1] == IND_CODE)
	{
		arg = get_arg(data, carr, &rel_pos, 0);
		put_reg_value_on_arena(data->arena,
							   (int)reg_value, arg % MEM_SIZE);
	}
	else if (carr->args[1] == REG_CODE)
	{
		arg = data->arena[carr->cur_pos];
		carr->reg[(arg)] = reg_value;
	}
	set_next_op(carr, (carr->cur_pos + rel_pos) % MEM_SIZE);
}
