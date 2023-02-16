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
	size_t		len;

	if (av[i])
	{
		len = ft_strlen(av[i]);
		if (len < 4 || ft_strcmp(&av[i][len - 4], ".cor"))
			exit_error_message("Wrong player file extension!");
	}
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

void	validate_user_input(const int ac, const char **av, t_data *const data)
{
	int	i;
	int	flag_id;

	i = 1;
	flag_id = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-dump"))
		{
			validate_and_receive_dump_flag_arg(&i, av, ac, data);
			if (!av[i])
				break ;
			else
				continue ;
		}
		flag_id = validate_and_receive_n_flag(&i, av, ac);
		validate_file_extension(i, av);
		create_player(data);
		init_player(av[i], &data->player, flag_id);
		i++;
	}
	check_amount_of_players(data);
	check_n_flag_unique_ids(data);
	set_players_ids(data);
	sort_players_list(data);
}
