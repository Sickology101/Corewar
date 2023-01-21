/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/21 16:22:28 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_ld(t_data *const data, t_process *carriage)
{
	data->dump_cycles = 100000000;
	carriage->last_live = 0;
}
