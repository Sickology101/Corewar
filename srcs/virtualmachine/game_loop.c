/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:21:17 by igaplich          #+#    #+#             */
/*   Updated: 2023/01/14 20:39:37 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	run_game_loop(t_data *const data)
{
	while (data->process_amount)
	{
		if (data->cycles_from_begin == data->dump_cycles)
		{
			print_arena(data);
			exit(0);
		}
	}
}
