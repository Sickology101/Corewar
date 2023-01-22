/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/21 16:43:55 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_live(t_data *const data, t_process *carriage)
{
	// On live, it seems that we ALWAYS read 4 bytes(haven't found anything else yet)
	// "In its direct meaning, it represents itself" - so the address of the
	// next operation is at arena[t_dir] ?
	int	temp;

	temp = (data->arena[carriage->cur_pos + 1] | data->arena[carriage->cur_pos + 2]
			| data->arena[carriage->cur_pos + 3] | data->arena[carriage->cur_pos + 4]);
	//if (temp < 0)
	//	;
	carriage->next_operation = temp % MEM_SIZE;

	carriage->op_id = 1;
	carriage->cycles_before_exec = 10;
	printf("\n\t you've reached set_live\n");
	//if (carriage->cur_pos == 4095)
	//	carriage->reg = get_args(data->arena[0]);
	//else
	//	carriage->reg = get_args(data->arena[carriage->cur_pos + 1]);
	//first switch = 0;
	//second switch = 0;
}
