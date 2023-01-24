/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/24 20:14:05 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_live(t_data *const data, t_process *carriage)
{
	int	temp;

	temp = calculate_args(DIR_CODE, data->arena[carriage->cur_pos + 1]
			| data->arena[carriage->cur_pos + 2]
			| data->arena[carriage->cur_pos + 3]
			| data->arena[carriage->cur_pos + 4]);
	carriage->last_live = data->counter->total_cycles;
	if (temp < 0 && (temp * -1) <= data->player_amount)
		data->last_alive = temp;
	carriage->op_id = 1;
	carriage->cycles_before_exec = 10;
	printf("\n\t you've reached set_live\n");
}

/*	TEMPORARY COMMENT(from cookbook):
The live statement has two functions:

	It counts that carriage, which performs the live statement, is alive.
		> done on line 23.

	If the number specified as an argument to the statement live 
	matches the number of the player, 
	then it will consider that the player is alive. 
	For example, if the argument value is -2, 
	then the player with the number 2 is alive.
		> done on line 24-25
			> Must still check whether it has to be negative number or not!
			> Need to change either data->last_alive to (int),
				OR we find the address to the player here.
*/
