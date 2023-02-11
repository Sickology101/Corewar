/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_ids.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:32:14 by igaplich          #+#    #+#             */
/*   Updated: 2023/01/17 15:10:23 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	find_free_id(t_data *const data, int *missing_id)
{	
	t_player	*tmp_player;

	tmp_player = data->player;
	while (tmp_player)
	{
		if (tmp_player->id == *missing_id)
		{
			*missing_id = *missing_id - 1;
			tmp_player = data->player;
			continue ;
		}
		tmp_player = tmp_player->next;
	}
}

void	check_amount_of_players(t_data *const data)
{
	t_player	*tmp;
	int			counter;

	counter = 1;
	tmp = data->player;
	if (!tmp)
		exit_error_message("Not enough players");
	while (tmp)
	{
		if (counter > MAX_PLAYERS)
			exit_error_message("Too many players - maximum amount is 4!");
		if (tmp->id > data->player_amount)
			exit_error_message("-n player number is higher "
				"than amount of players!");
		tmp = tmp->next;
		counter++;
	}
}

void	set_players_ids(t_data *const data)
{
	int			missing_id;
	t_player	*tmp_player;

	missing_id = data->player_amount;
	tmp_player = data->player;
	while (tmp_player)
	{
		find_free_id(data, &missing_id);
		if (tmp_player->id == 0)
			tmp_player->id = missing_id;
		tmp_player = tmp_player->next;
	}
}

void	find_id_and_swap_players(t_player *to_player, int req_id)
{
	t_player	*iter;
	int			tmp_id;
	const char	*tmp_path;

	iter = to_player->next;
	tmp_path = NULL;
	tmp_id = 0;
	while (iter->id != req_id)
		iter = iter->next;
	tmp_id = iter->id;
	iter->id = to_player->id;
	to_player->id = tmp_id;
	tmp_path = iter->path;
	iter->path = to_player->path;
	to_player->path = tmp_path;
}

void	sort_players_list(t_data *const data)
{
	int			tmp_id;
	t_player	*iter;

	tmp_id = 1;
	iter = data->player;
	while (tmp_id <= data->player_amount)
	{
		if (iter->id != tmp_id)
		{
			find_id_and_swap_players(iter, tmp_id);
		}
		tmp_id++;
		iter = iter->next;
	}
}
