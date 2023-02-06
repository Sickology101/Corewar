/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:40:29 by igaplich          #+#    #+#             */
/*   Updated: 2023/02/02 17:22:20 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	free_process(t_process *process)
{
	process->player = NULL;
	process->next = NULL;
	free (process);
}

void	create_initial_process_list(t_data *const data)
{
	t_process	*new_process;

	if (!data->process_head)
	{
		data->process_head = (t_process *)malloc(sizeof(t_process));
		if (!data->process_head)
			exit_error_message("Process head allocation failed!");
		data->process_tail = data->process_head;
		data->process_head->next = NULL;
		data->process_head->unique_id = data->player_amount;
	}
	else
	{
		new_process = (t_process *)malloc(sizeof(t_process));
		if (!new_process)
			exit_error_message("Process head allocation failed!");
		new_process->unique_id = data->process_head->unique_id - 1;
		new_process->next = data->process_head;
		data->process_head = new_process;
	}
}

void	init_process(t_data *const data, t_process *process, size_t pointer)
{
	int	i;

	i = 0;
	while (i < 16)
		process->reg[i++] = 0;
	process->args[0] = 0;
	process->args[1] = 0;
	process->args[2] = 0;
	process->carry = 0;
	process->op_id = 0;
	process->rel_pos = 0;
	process->last_live = 0;
	process->cycles_before_exec = 0;
	process->cur_pos = pointer;
	process->player = NULL;
	data->process_amount++;
}

/*
** DELETE put_process_on_arena IF NOT NEEDED!
*/
void	put_process_on_arena(t_data *const data,
		t_process *copy, int start, int end)
{
	int	i;

	i = 0;
	while (start <= end)
	{
		data->arena[copy->cur_pos + i] = data->arena[start];
		printf("new: %0.2x\n", data->arena[copy->cur_pos + i]);
		start++;
		i++;
	}
}

t_process	*copy_process(t_data *const data, t_process *carriage, int address)
{
	int			i;
	t_process	*copy;

	copy = (t_process *)malloc(sizeof(t_process));
	if (!copy)
		exit_error_message("Process allocation failed!");
	init_process(data, copy, (carriage->cur_pos + address) % MEM_SIZE);
	copy->unique_id = data->process_amount;
	copy->next = NULL;
	copy->carry = carriage->carry;
	copy->last_live = carriage->last_live;
	i = -1;
	while (++i < REG_NUMBER)
		copy->reg[i] = carriage->reg[i];
	return (copy);
}
