/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/26 20:19:36 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

/*
** set_live is the most important statement in the game,
** because it tells if the champion is alive.
** The function identifies the live-statement to the process,
** and the champion that is mentioned in the argument.
*/
void	set_live(t_data *const data, t_process *carriage)
{
	int			player_id;
	t_player	*player;
	int			idx;

	idx = 0;
	carriage->rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	player_id = get_arg(data, carriage, 0, idx);
	data->counter.lives_this_period++;
	carriage->last_live = data->counter.cycles_total;
	if (player_id <= -1 && player_id >= -((int32_t)data->player_amount))
	{
		player = data->player;
		while (player->id != -player_id)
			player = player->next;
		data->last_alive = player_id;
		player->last_live = data->counter.cycles_total;
		player->lives_amount++;
	}
	printf("\n\t you've reached set_live, arg: %i\n", player_id);
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
			> Must be a negative number! (2 doesn't count, '-2' does!)
			> Need to change either data->last_alive to (int),
				OR we find the address to the player here.
*/
