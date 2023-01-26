/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:30:33 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/26 20:42:58 by mtissari         ###   ########.fr       */
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

int	make_dir_to_int(uint8_t *arena, int cur_pos, int dir_size)
{
	int	res;

	if (dir_size == 4)
	{
		res = arena[(cur_pos) % MEM_SIZE] << 24
			| arena[(cur_pos + 1) % MEM_SIZE] << 16
			| arena[(cur_pos + 2) % MEM_SIZE] << 8
			| arena[(cur_pos + 3) % MEM_SIZE];
	}
	else
	{
		res = 0;
		res = arena[(cur_pos) % MEM_SIZE] << 8
			| arena[(cur_pos + 1) % MEM_SIZE];
	}
	return (res);
}

int	make_ind_to_int(uint8_t *arena, int cur_pos)
{
	int	res;

	res = 0;
	res = arena[(cur_pos) % MEM_SIZE] << 8
		| arena[(cur_pos + 1) % MEM_SIZE];
	return (res);
}

/*
** Calculate_args converts the unsigned ints to signed int16_t's,
** which is the way we get the negatives when we need them.
*/
int	calculate_args(int code, int args)
{
	int16_t	ind;
	int		ret;

	ret = 0;
	if (code == IND_CODE)
	{
		ind = args;
		ind = ind % IDX_MOD;
		ret = ind;
	}
	else if (code == DIR_CODE)
	{
		ret = args;
	}
	else if (code == REG_CODE)
	{
		if (args < 1 || args > 16) // invalid reg, just ignore and skip?
			return (-1);
		ret = args - 1;
	}
	return (ret);
}

void	set_next_op(t_process *carriage, int jump_to)
{
	carriage->next_operation = jump_to;
}

void	put_reg_value_on_arena(uint8_t *arena, int value, int pos)
{
	int		i;

	i = 0;
	arena[pos + i++] = (value & 0xFF000000) >> 24;
	arena[pos + i++] = (value & 0x00FF0000) >> 16;
	arena[pos + i++] = (value & 0x0000FF00) >> 8;
	arena[pos + i++] = (value & 0x000000FF) >> 0;
}
