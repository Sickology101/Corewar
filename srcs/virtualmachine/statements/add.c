/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:05:56 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/27 19:26:56 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

/*
** set_sub sets the value of the third argument as argument1 + argument2.
*/
void	set_add(t_data *const data, t_process *carr)
{
	int	arg1;
	int	arg2;
	int	arg3;
	int	rel_pos;

	rel_pos = 1 + g_op[carr->op_id - 1].read_types;
	arg1 = get_arg(data, carr, &rel_pos, 0);
	arg2 = get_arg(data, carr, &rel_pos, 1);
	arg3 = get_arg(data, carr, &rel_pos, 2);
	if (arg1 != -1 && arg2 != -1 && arg3 != -1)
	{
		carr->reg[arg3] = carr->reg[arg1] + carr->reg[arg2];
	}
	set_carry(carr, arg3);
	set_next_op(carr, (carr->cur_pos + 5) % MEM_SIZE);
	printf("arena now [%.2x] and next [%.2x]", data->arena[carr->cur_pos], data->arena[carr->next_operation]);
}
