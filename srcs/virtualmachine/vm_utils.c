/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:30:33 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/24 20:50:34 by mtissari         ###   ########.fr       */
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

/*
** Calculate_args converts the unsigned ints to signed int16_t's,
** which is the way we get the negatives when we need them.
*/
int	calculate_args(int code, int args)
{
	int16_t	ind;
	int		ret;

	if (code == 3) // (IND_CODE)
	{
		ind = args;
		ind = ind % IDX_MOD;
		printf("\targument value: %i\n", ind);
		ret = ind;
	}
	else if (code == 2) // (DIR_CODE)
	{
		ret = args;
	}
	else if (code == 1) // (REG_CODE)
	{
		if (args < 1 || args > 16) // invalid reg, just ignore and skip?
			return (0);
		ret = args;
	}
	return (ret);
}
