/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/26 20:46:48 by mtissari         ###   ########.fr       */
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
void	set_st(t_data *const data, t_process *carriage)
{
	int	arg;
	int	reg;

	if (carriage->args[1] == IND_CODE)
	{
		arg = make_ind_to_int(data->arena, (carriage->cur_pos + 3) % MEM_SIZE);
		arg = calculate_args(IND_CODE, arg);
		reg = 0;
		reg = data->arena[(carriage->cur_pos + 2) % MEM_SIZE];
		reg = calculate_args(IND_CODE, reg);
		if (reg != -1)
			put_reg_value_on_arena(data->arena,
				reg, (carriage->cur_pos + arg) % MEM_SIZE);
	}
	else if (carriage->args[1] == REG_CODE)
	{
		carriage->reg[data->arena[(carriage->cur_pos + 3) % MEM_SIZE]]
			= carriage->reg[data->arena[(carriage->cur_pos + 2) % MEM_SIZE]];
	}
	printf("\n\n\t\tyou've reached set_st\n");
}
