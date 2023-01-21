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
	carriage->operation_code = 1;
	carriage->cycles_before_exec = 10;
	printf("\n\t you've reached set_live\n");
	//if (carriage->cur_pos == 4095)
	//	carriage->reg = get_args(data->arena[0]);
	//else
	//	carriage->reg = get_args(data->arena[carriage->cur_pos + 1]);
	//first switch = 0;
	//second switch = 0;
}
