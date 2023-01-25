/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:06 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/25 20:09:55 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_ldi(t_data *const data, t_process *carriage)
{
	data->counter.total_cycles++;
	data->counter.total_cycles--;
	carriage->last_live = 0;
}
