/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:37:31 by macbook           #+#    #+#             */
/*   Updated: 2023/01/12 20:37:34 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	init_data(t_data *data)
{
	data->player = NULL;
	data->last_alive = NULL;
	data->player_amount = 0;
	data->cycles_from_begin = 0;
	data->amount_of_live = 0;
	data->cycles_to_die = CYCLE_TO_DIE;
	data->process_amount = 0;
	data->process_head = NULL;
	data->process_tail = NULL;
}

void	init_player(const char *path, t_player **player, int flag_id)
{
	if (flag_id != 0)
		(*player)->id = flag_id;
	else
		(*player)->id = 0;
	(*player)->fd = 0;
	(*player)->path = path;
	(*player)->name = NULL;
	(*player)->comment = NULL;
	(*player)->exec_size = 0;
	(*player)->exec_code = 0;
}

void	place_players_on_arena(t_player *player, t_data *const data,
					size_t pointer)
{
	size_t	i;

	i = 0;
	while (i < player->exec_size)
	{
		data->arena[pointer + i] = player->exec_code[i];
		i++;
	}
}

void	init_process_on_arena(t_data *const data, t_player *player,
					size_t pointer)
{
	create_initial_process_list(data);
	data->process_head->carry = 0;
	data->process_head->operation_code = 0;
	data->process_head->last_live = 0;
	data->process_head->cycles_before_exec = 0;
	data->process_head->cur_pos = pointer;
	data->process_head->next_operation = 0;
	data->process_head->reg[0] = -(player->id);
	data->process_head->player = player;
	data->process_amount++;
}

void	init_arena(t_data *const data)
{
	int			i;
	t_player	*player;
	size_t		pointer;

	i = -1;
	while (++i < MEM_SIZE)
		data->arena[i] = 0;
	i = 0;
	pointer = 0;
	player = data->player;
	while (i < data->player_amount)
	{
		print_player_code(player);
		place_players_on_arena(player, data, pointer);
		init_process_on_arena(data, player, pointer);
		i++;
		pointer += MEM_SIZE / data->player_amount;
		player = player->next;
	}
	print_arena(data);
}
