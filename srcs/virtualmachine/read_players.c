/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:35:42 by igaplich          #+#    #+#             */
/*   Updated: 2023/01/11 17:35:44 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	validate_file_extension(const int i, const char **av)
{
	const char	*dot;

	dot = ft_strchr(av[i], '.');
	if (!dot)
		exit_error_message("Wrong player file extension!");
	else if (dot == av[i])
		exit_error_message("Empty player name!");
	else
	{
		if (ft_strcmp(dot, ".cor"))
			exit_error_message("Wrong player file extension!");
	}
}

void	init_player(const char *name, t_player **player, int flag_id)
{
	(*player)->name = name;
	(*player)->comment = NULL;
	if (flag_id != 0)
		(*player)->id = flag_id;
	else
		(*player)->id = 0;
}

void	create_player(t_data *const data)
{
	t_player	*new_player;

	new_player = (t_player *)malloc(sizeof(t_player));
	if (!new_player)
		exit_error_message("Player allocation failed!");
	new_player->next = NULL;
	if (data->player)
	{
		new_player->next = data->player;
		data->player = new_player;
	}
	else if (!data->player)
		data->player = new_player;
	data->player_amount++;
}

void	open_players(const int ac, const char **av, t_data *const data)
{
	int	i;
	int	flag_id;

	i = 1;
	flag_id = 0;
	while (i < ac)
	{
		flag_id = validate_and_receive_n_flag_arg(&i, av, ac);
		validate_file_extension(i, av);
		create_player(data);
		init_player(av[i], &data->player, flag_id);
		i++;
	}
	check_amount_of_players(data);
	set_players_ids(data);
}
