/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:05:59 by mtissari          #+#    #+#             */
/*   Updated: 2023/02/08 13:32:15 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_aff(t_data *const data, t_process *carriage)
{
	int32_t	value;
	int		idx;

	idx = 0;
	carriage->rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	value = get_arg(data, carriage, 0, idx);
	//ft_printf("Aff: %c\n", (char)value);
}
