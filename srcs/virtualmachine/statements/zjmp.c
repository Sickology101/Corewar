/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/30 17:27:34 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

/*
** set_zjmp relocates the process on the arena to the place the argument says,
** but only if the carry is 1. Otherwise we carry on as usual.
*/
void	set_zjmp(t_data *const data, t_process *carriage)
{
	int	address;

	carriage->rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	address = get_arg(data, carriage, &carriage->rel_pos, 0);
	if (carriage->carry)
	{
		carriage->cur_pos = protect_address(carriage->cur_pos + (address % IDX_MOD));
		carriage->rel_pos = 0;
	}
}
