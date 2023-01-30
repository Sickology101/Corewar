/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:05:56 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/30 17:40:53 by mtissari         ###   ########.fr       */
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
	int	reg_id;
	int	rel_pos;

	print_arena(data);
	rel_pos = 1 + g_op[carr->op_id - 1].read_types;
	arg1 = get_arg(data, carr, &rel_pos, 0);
	arg2 = get_arg(data, carr, &rel_pos, 1);
	reg_id = data->arena[carr->cur_pos + rel_pos] - 1;
	carr->reg[reg_id] = arg1 + arg2;
	set_carry(carr, reg_id);
	set_next_op(carr, (carr->cur_pos + rel_pos) % MEM_SIZE);
	printf("arena now [%.2x] and next [%.2x]", data->arena[carr->cur_pos], data->arena[carr->next_operation]);
}
