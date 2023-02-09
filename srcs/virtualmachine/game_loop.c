/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:21:17 by igaplich          #+#    #+#             */
/*   Updated: 2023/02/09 19:11:19 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	init_counter(t_counter *counter)
{
	counter->cycles_total = 0;
	counter->cycles_to_die = CYCLE_TO_DIE;
	counter->cycles_after_check = 0;
	counter->checks_total = 0;
	counter->lives_this_period = 0;
}

/*
** delete_process takes care that no matter where we are deleting process
** from in the list, the list stays 
*/
void	delete_process(t_data *const data, t_process *process)
{
	t_process	*prev;

	if (process != data->process_head)
	{
		prev = data->process_head;
		while (prev->next != process)
			prev = prev->next;
		prev->next = process->next;
	}
	else
		data->process_head = process->next;
	free_process(process);
	prev = NULL;
	data->process_amount--;
	printf("PROCESS DELETED! nb of processes now: %zu\n", data->process_amount);
}

void	check_processes(t_data *const data)
{
	t_process	*temp_process;
	t_process	*after_temp;

	temp_process = data->process_head;
	while (temp_process != NULL)
	{
		after_temp = temp_process->next;
		if (data->counter.cycles_to_die <= data->counter.cycles_total
			- temp_process->last_live)
		{
			delete_process(data, temp_process);
		}
		temp_process = after_temp;
	}
}

/*
** in perform_check we check the whole list of processes and check if they are 
** dead. When dead, we delete them from list. If we received more than NBR_LIVE
** amount of live -statements, we reduce the CYCLE_TO_DIE by CYCLE_DELTA.
** We start a new period with the amount of CYCLES_TO_DIE,
** unless it's 0 or less. In this case we just set the period to 1.
**
** (with period we mean the time between checks)
*/
void	perform_check(t_data *const data, t_counter *counter)
{
	int			i;
	t_player	*player;

	i = 0;
	counter->checks_total++;
	check_processes(data);
	if (counter->lives_this_period >= NBR_LIVE
		|| counter->checks_total == MAX_CHECKS)
	{
		counter->cycles_to_die -= CYCLE_DELTA;
		counter->checks_total = 0;
	}
	player = data->player;
	while (player)
	{
		player->lives_amount = 0;
		player = player->next;
	}
	counter->lives_this_period = 0;
	counter->cycles_after_check = 0;
}

/*
** run_game_loop is the game itself. Here we perform different checks and
** execute the commands of the players.
*/
void	run_game_loop(t_data *const data)
{
	printf("\n\ndump: %i\n\n", data->dump_cycles);
	init_counter(&data->counter);
	while (data->process_amount)
	{
		if (data->counter.cycles_total == data->dump_cycles)
		{
			print_arena(data);
			exit(0);
		}
		perform_cycle(data);
		if (data->counter.cycles_to_die <= 0
			|| data->counter.cycles_to_die == data->counter.cycles_after_check)
			perform_check(data, &data->counter);
	}
}
