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

void	init_player(const int i, const char **av, t_player **player)
{
	(*player)->name = av[i];
	(*player)->comment = NULL;
	(*player)->id = i;
}

void	create_player(const int i, const char **av, t_data * const data)
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
	init_player(i, av, &data->player);
}

int argument_has_only_numbers(int *i, const char **av)
{
	size_t iterator;

	iterator = 0;
	while (av[*i][iterator])
	{
		if (av[*i][iterator] >= '0' && av[*i][iterator] <= '9')
			iterator++;
		else
			return (0);
	}
	return (1);
}


void	n_flag_validation(int *i, const char **av, int ac)
{
	if (*av[*i] == '-')
	{
		if (!ft_strcmp(av[*i], "-n"))
		{
			if ((*i + 2) >= ac)
				exit_error_message("Too few arguments after -n flag!");
			*i = *i + 1;
			if (!argument_has_only_numbers(i, av))
				exit_error_message("Wrong argument after -n flag!");
			*i = *i + 1;
		}
		else
			exit_error_message("Unsupported flag!");
	}
}

void	open_players(const int ac, const char **av, t_data * const data)
{
	int	i;
	
	i = 1;
	while (i < ac)
	{
		n_flag_validation(&i, av, ac);
		validate_file_extension(i, av);
		create_player(i, av, data);
		i++;
	}

}