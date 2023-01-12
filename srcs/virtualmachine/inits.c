/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:37:31 by macbook           #+#    #+#             */
/*   Updated: 2023/01/12 20:37:34 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	init_data(t_data *data)
{
	data->player = NULL;
	data->player_amount = 0;
}

void	init_player(const char *path, t_player **player, int flag_id)
{
	if (flag_id != 0)
		(*player)->id = flag_id;
	else
		(*player)->id = 0;
	(*player)->fd = 0;
	(*player)->path = path;
	(*player)->name = NULL;
	(*player)->comment = NULL;
	(*player)->exec_size = 0;
	(*player)->exec_code = 0;
}
