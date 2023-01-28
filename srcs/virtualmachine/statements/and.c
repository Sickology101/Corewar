/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:01 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/27 19:41:26 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

static void	execute_and_statement(t_process *carr, int arg1, int arg2, int arg3)
{
	if (carr->args[0] == REG_CODE)
		arg1 = carr->reg[arg1];
	if (carr->args[1] == REG_CODE)
		arg2 = carr->reg[arg2];
	printf("\t\t\t|||EXECUTE 'AND': arg1: |%i|, arg2: |%i|, arg3: |%i|||\n\n",
		arg1, arg2, arg3);
	carr->reg[arg3] = (arg1 & arg2);
}

void	set_and(t_data *const data, t_process *carr)
{
	int	arg1;
	int	arg2;
	int	arg3;
	int	rel_pos;

	rel_pos = 1 + g_op[carr->op_id - 1].read_types;
	arg1 = get_arg(data, carr, &rel_pos, 0);
	arg2 = get_arg(data, carr, &rel_pos, 1);
	arg3 = get_arg(data, carr, &rel_pos, 2);
	execute_and_statement(carr, arg1, arg2, arg3);
	set_carry(carr, arg3);
	set_next_op(carr, (carr->cur_pos + 2 + rel_pos) % MEM_SIZE);
}
