/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_statement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:57:17 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/19 18:38:15 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	three_arguments(t_data *const data, t_process *carriage, uint8_t code)
{
	if (code == 4)
		set_add(data, carriage);
	if (code == 5)
		set_sub(data, carriage);
	if (code == 6)
		set_and(data, carriage);
	if (code == 7)
		set_or(data, carriage);
	if (code == 7)
		set_xor(data, carriage);
	if (code == 10)
		set_ldi(data, carriage);
	if (code == 11)
		set_sti(data, carriage);
	if (code == 14)
		set_lldi(data, carriage);
}

void	two_arguments(t_data *const data, t_process *carriage, uint8_t code)
{
	if (code == 2)
		set_ld(data, carriage);
	if (code == 3)
		set_st(data, carriage);
	if (code == 13)
		set_lld(data, carriage);
}

void	one_argument(t_data *const data, t_process *carriage, uint8_t code)
{
	if (code == 1)
		set_live(data, carriage);
	if (code == 9)
		set_zjmp(data, carriage);
	if (code == 12)
		set_fork(data, carriage);
	if (code == 15)
		set_lfork(data, carriage);
	if (code == 16)
		set_aff(data, carriage);
}

void	check_statement(t_data *const data, t_process *carriage)
{
	uint8_t	code;

	code = data->arena[carriage->cur_pos];
	if (code >= 1 && code <= 16)
	{
		carriage->operation_code = code;
		if (code == 1 || code == 9 || code == 12 || code == 15 || code == 16)
			one_argument(data, carriage, code);
		else if (code == 2 || code == 3 || code == 13)
			two_arguments(data, carriage, code);
		else if (code == 4 || code == 5 || code == 6 || code == 7 || code == 8
			|| code == 10 || code == 11 || code == 14)
			three_arguments(data, carriage, code);
	}
	else
		not_a_statement(data);
}

/*
** check_statement reads which statement is in question. That information tells
** us already how many arguments we will have. This could be called from 
** set_statement_codes and execute_statement.
*/
