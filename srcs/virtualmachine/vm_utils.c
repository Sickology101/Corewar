/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:30:33 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/27 18:58:31 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

int	swap_endians(int buffer)
{
	int	leftmost;
	int	left_middle;
	int	right_middle;
	int	rightmost;

	leftmost = (buffer & 0x000000FF) >> 0;
	left_middle = (buffer & 0x0000FF00) >> 8;
	right_middle = (buffer & 0x00FF0000) >> 16;
	rightmost = (buffer & 0xFF000000) >> 24;
	leftmost <<= 24;
	left_middle <<= 16;
	right_middle <<= 8;
	rightmost <<= 0;
	return (leftmost | left_middle | right_middle | rightmost);
}

void	put_reg_value_on_arena(uint8_t *arena, int value, int pos, int size)
{
	int		i;

	i = 0;
	if (pos < 0)
		pos += MEM_SIZE;
	if (size == 4)
	{
		arena[(pos + i++) % MEM_SIZE] = (value & 0xFF000000) >> 24;
		arena[(pos + i++) % MEM_SIZE] = (value & 0x00FF0000) >> 16;
	}
	arena[(pos + i++) % MEM_SIZE] = (value & 0x0000FF00) >> 8;
	arena[(pos + i++) % MEM_SIZE] = (value & 0x000000FF);
}

int	calc_relative_position(int arg, t_process *carriage)
{
	if (arg == DIR_CODE)
		return (g_op[carriage->op_id - 1].tdir_size);
	else if (arg == IND_CODE)
		return (2);
	else if (arg == REG_CODE)
		return (1);
}

void	set_carry(t_process *carriage, int value)
{
	if (!value)
		carriage->carry = 1;
	else
		carriage->carry = 0;
}
