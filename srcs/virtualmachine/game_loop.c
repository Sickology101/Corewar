/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:21:17 by igaplich          #+#    #+#             */
/*   Updated: 2023/01/17 18:13:27 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	init_counter(t_counter *counter)
{
	counter->total_cycles = 0;
	counter->cycles_to_die = CYCLE_TO_DIE;
	counter->nb_of_checks_done = 0;
	counter->lives_this_period = 0;
	counter->player = 0;
}

void	reduce_cycle_bf_execution(t_data *const data)
{
	t_process	*temp_process;

	temp_process = data->process_head;
	while (temp_process != NULL)
	{
		if (temp_process->cycles_before_exec >= 0)
			temp_process->cycles_before_exec--;
	}
}

void	free_process(t_process *process)
{
	process->player = NULL;
	process->next = NULL;
	free (process);
}

void	delete_process(t_data *const data, t_process *process)
{
	t_process	*prev;

	if (process != data->process_head)
	{
		prev = data->process_head;
		while (prev->next != process)
			prev = prev->next;
		prev->next = process->next;
		if (prev->next == NULL)
			data->process_tail = prev;
	}
	else
		data->process_head = process->next;
	free_process(process);
	prev = NULL;
	data->process_amount--;
}

/*
** delete_process takes care that no matter where we are deleting process
** from in the list, the list stays 
*/

void	perform_check(t_data *const data, t_counter *counter)
{
	t_process	*temp_process;

	temp_process = data->process_head;
	while (temp_process != NULL)
	{
		if (temp_process->cycles_before_exec <= 0
			|| temp_process->last_live - CYCLE_TO_DIE < 0)
			delete_process(data, temp_process);
	}
	if (counter->lives_this_period >= NBR_LIVE)
		CYCLE_TO_DIE -= CYCLE_DELTA;
	if (CYCLE_TO_DIE >= 0)
		counter->cycles_do_die = CYCLE_TO_DIE;
	else
		counter->cycles_do_die = 1;
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

void	run_game_loop(t_data *const data)
{
	t_counter	counter;

	init_counter(&counter);
	while (data->process_amount)
	{
		if (data->cycles_from_begin == data->dump_cycles)
		{
			print_arena(data);
			exit(0);
		}
		//set_statement_codes();
		reduce_cycle_bf_execution(data);
		//execute_statements_and_move_processes();
		if (counter->cycles_to_die <= 0)
			perform_check(data, &counter);
		data->cycles_from_begin++;
	}
}

/*
** run_game_loop is the game itself. Here we perform different checks and
** execute the commands of the players.
*/
