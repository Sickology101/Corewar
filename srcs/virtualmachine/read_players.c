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

void	create_and_init_player(const char *path,
								t_data *const data, int flag_id)
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
	data->player->path = path;
	data->player->comment = NULL;
	if (flag_id != 0)
		data->player->id = flag_id;
	else
		data->player->id = 0;
}

void	check_n_flag_unique_ids(t_data *const data)
{
	char		ids[4];
	t_player	*tmp;
	int			i;

	i = -1;
	while (++i < data->player_amount)
		ids[i] = 0;
	tmp = data->player;
	while (tmp)
	{
		if (tmp->id != 0 && ids[tmp->id - 1] == 0)
			ids[tmp->id - 1] = 1;
		else if (tmp->id != 0 && ids[tmp->id - 1] != 0)
			exit_error_message("-n number is used multiple times!");
		tmp = tmp->next;
	}
}

void	validate_user_input(const int ac, const char **av, t_data *const data)
{
	int	i;
	int	flag_id;

	i = 1;
	flag_id = 0;
	while (i < ac)
	{
		flag_id = validate_and_receive_n_flag_arg(&i, av, ac);
		validate_file_extension(i, av);
		create_and_init_player(av[i], data, flag_id);
		i++;
	}
	check_amount_of_players(data);
	check_n_flag_unique_ids(data);
	set_players_ids(data);
	sort_players_list(data);
}
