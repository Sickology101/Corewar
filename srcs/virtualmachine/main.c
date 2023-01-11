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

void	init_data(t_data *data)
{
	data->player = NULL;
	data->player_amount = 0;
}

int	main(const int ac, const char **av)
{
	t_data	data;

	init_data(&data);
	if (ac < 2)
		exit_error_message("Not enough players!");
	open_players(ac, av, &data);
	while (data.player)
	{
		printf("%s ", data.player->name);
		printf("id = %d\n", data.player->id);
		data.player = data.player->next;
	}
	return (0);
}
