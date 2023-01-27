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
	int8_t	reg;

	reg = data->arena[(carr->cur_pos + 2) % MEM_SIZE];
	reg = calculate_args(IND_CODE, reg);
	if (reg != -1)
	{
		arg = calculate_args(REG_CODE,
				(int)carr->reg[data->arena[(carr->cur_pos + 3) % MEM_SIZE]]);
		if (carr->args[1] == IND_CODE)
		{
			arg = make_ind_to_int(data->arena, (carr->cur_pos + 3) % MEM_SIZE);
			arg = calculate_args(IND_CODE, arg);
			put_reg_value_on_arena(data->arena,
				(int)carr->reg[reg], (carr->cur_pos + arg) % MEM_SIZE);
		}
		else if (carr->args[1] == REG_CODE && arg != -1)
		{
			carr->reg[(arg)] = carr->reg[reg];
		}
	}
	printf("\n\n\t\tyou've reached set_st\n");
	if (carr->args[1] == IND_CODE)
		set_next_op(carr, (carr->cur_pos + 5) % MEM_SIZE);
	else
		set_next_op(carr, (carr->cur_pos + 4) % MEM_SIZE);
}
