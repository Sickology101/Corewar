/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:23:35 by marius            #+#    #+#             */
/*   Updated: 2023/01/12 17:44:58 by mtissari         ###   ########.fr       */
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
}

int	main(const int ac, const char **av)
{
	t_data	data;

	init_data(&data);
	if (ac < 2)
		exit_error_message("Not enough players!");
	open_players(ac, av, &data);
	printf("%s\n", data.player->name);
	return(0);
}
