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

void	validate_and_receive_dump_flag_arg(int *i, const char **av, int ac,
								t_data *const data)
{
	size_t	j;

	if ((*i + 1) >= ac)
		exit_error_message("Too few arguments after flag!");
	*i = *i + 1;
	j = 0;
	while (av[*i][j])
	{
		if (!ft_isdigit(av[*i][j]))
			exit_error_message("Wrong argument after -dump flag!");
		j++;
	}
	if (data->dump_cycles == -1)
		data->dump_cycles = ft_atoi(av[*i]);
	else
		exit_error_message("-dump set multiple times!");
	*i = *i + 1;
}

int	validate_and_receive_n_flag(int *i, const char **av, int ac)
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

	if (av[i])
	{
		dot = ft_strchr(av[i], '.');
		if (!dot)
			exit_error_message("Wrong player file extension!");
		else if (dot == av[i] && *(dot - 1) && *(dot - 1) == '/')
			exit_error_message("Empty player filename!");
		else if (dot == av[i] && *(dot + 1) && *(dot + 1) == '/')
			exit_error_message("Enter player filename without "
				"starting from ./");
		else
		{
			if (ft_strcmp(dot, ".cor"))
				exit_error_message("Wrong player file extension "
					"or dots in the path!");
		}
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
