/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:05:59 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/25 20:09:46 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_aff(t_data *const data, t_process *carriage)
{
	int32_t	value;
	int		rel_pos;

	rel_pos = 1 + g_op[carriage->op_id - 1].read_types;
	value = get_arg(data, carriage, &rel_pos, 0);
	ft_printf("Aff: %c\n", (char)value);
}
