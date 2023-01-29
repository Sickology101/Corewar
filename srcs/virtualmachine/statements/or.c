/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/25 20:10:10 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_or(t_data *const data, t_process *carriage)
{
	int arg1;
	int	arg2;
	int	arg3;
	int	rel_pos;

	rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	arg1 = get_arg(data, carriage, &rel_pos, 0);
	arg2 = get_arg(data, carriage, &rel_pos, 1);
	arg3 = get_arg(data, carriage, &rel_pos, 2);
	if (carriage->args[0] == REG_CODE)
		arg1 = carriage->reg[arg1];
	if (carriage->args[1] == REG_CODE)
		arg2 = carriage->reg[arg2];
	printf("\t\t\t|||EXECUTE 'OR': arg1: |%i|, arg2: |%i|, arg3: |%i|||\n\n",
		arg1, arg2, arg3);
	carriage->reg[arg3] = (arg1 | arg2);
	set_carry(carriage, arg3);
	set_next_op(carriage, (carriage->cur_pos + rel_pos) % MEM_SIZE);
}
