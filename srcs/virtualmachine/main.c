/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:23:35 by marius            #+#    #+#             */
/*   Updated: 2023/01/08 14:23:41 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	exit_error_message(char *message)
{
	ft_putendl(message);
	exit(0);
}

void	validate_file_extension(const int i, const char **av)
{
	const char *dot;

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

void	open_players(const int ac, const char **av, t_data * const data)
{
	int	i;
	
	i = 1;
	while (i < ac)
	{
		validate_file_extension(i, av);
		create_player(i, av, data);
		i++;
	}

}

void	init_data(t_data *data)
{
	data->player = NULL;
}

int	main(const int ac, const char **av)
{
	t_data	data;

	init_data(&data);
	if (ac < 2)
		exit_error_message("Not enough players!");
	open_players(ac, av, &data);

	return(0);
}
