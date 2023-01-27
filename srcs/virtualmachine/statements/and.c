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

static void	execute_and_satement(t_process *carr, int arg1, int arg2, int arg3)
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

	printf("\t\tyou've reached set_and!\n");
	arg1 = get_arg(data, carr, (carr->cur_pos + 2) % MEM_SIZE, carr->args[0]);
	if (carr->args[0] == DIR_CODE)
		arg2 = get_arg(data, carr,
				(carr->cur_pos + 6) % MEM_SIZE, carr->args[1]);
	else if (carr->args[0] == IND_CODE)
		arg2 = get_arg(data, carr,
				(carr->cur_pos + 4) % MEM_SIZE, carr->args[1]);
	else
		arg2 = get_arg(data, carr,
				(carr->cur_pos + 3) % MEM_SIZE, carr->args[1]);
	if (carr->args[1] == IND_CODE)
		arg2 = make_dir_to_int(data->arena,
				(carr->cur_pos + arg2) % MEM_SIZE, 4);
	rel_pos = calc_relative_position(carr->args[0], carr->args[1]);
	arg3 = calculate_args(REG_CODE,
			(int)data->arena[(carr->cur_pos + 1 + rel_pos) % MEM_SIZE]);
	execute_and_satement(carr, arg1, arg2, arg3);
	set_carry(carr, arg3);
	set_next_op(carr, (carr->cur_pos + 2 + rel_pos) % MEM_SIZE);
	printf("\tAND end\n");
}
