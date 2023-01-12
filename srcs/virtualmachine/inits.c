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

void	init_arena(t_data *const data)
{
	int			i;
	t_player	*player;
	int			pointer;

	i = -1;
	while (++i < MEM_SIZE)
		data->arena[i] = 0;
	i = 0;
	pointer = 0;
	player = data->player;
	while (i < data->player_amount)
	{
		ft_memcpy(&data->arena[pointer], &data->player->exec_code, //Argh, it kinda works, but probably we have to reverse data
			player->exec_size);									   //either here or when we read or save it into a player
		i++;
		pointer += MEM_SIZE / data->player_amount;
	}
	print_arena(data);
}
