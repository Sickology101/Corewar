/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:32:14 by igaplich          #+#    #+#             */
/*   Updated: 2023/01/11 19:32:17 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

int	validate_and_receive_n_flag_arg(int *i, const char **av, int ac)
{
	if (*av[*i] == '-')
	{
		if (!ft_strcmp(av[*i], "-n"))
		{
			if ((*i + 2) >= ac)
				exit_error_message("Too few arguments after -n flag!");
			*i = *i + 1;
			if (av[*i][0] < '1' || av[*i][0] > '4' || av[*i][1])
				exit_error_message("Wrong argument after -n flag!");
			*i = *i + 1;
			return (av[*i - 1][0] - '0');
		}
		else
			exit_error_message("Unsupported flag!");
	}
	return (0);
}

void	find_free_number(t_data *const data, int *missing_id)
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

	tmp = data->player;
	while (tmp)
	{
		if (tmp->id > data->player_amount)
			exit_error_message("-n player number is higher "
				"than amount of players!");
		tmp = tmp->next;
	}
}

void	set_players_ids(t_data *const data)
{
	int			missing_id;
	t_player	*tmp_player;

	missing_id = data->player_amount;
	find_free_number(data, &missing_id);
	tmp_player = data->player;
	while (tmp_player)
	{
		if (tmp_player->id == 0)
		{
			tmp_player->id = missing_id;
			missing_id--;
		}
		tmp_player = tmp_player->next;
	}
}
