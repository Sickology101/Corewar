/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:40:29 by igaplich          #+#    #+#             */
/*   Updated: 2023/01/14 16:40:30 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

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
