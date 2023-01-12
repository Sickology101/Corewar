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

int	main(const int ac, const char **av)
{
	t_data	data;

	init_data(&data);
	if (ac < 2)
		exit_error_message("Not enough players!");
	validate_user_input(ac, av, &data);
	validate_player(&data);
	print_champion_path_and_id(&data);
	print_introduction(&data);
	init_arena(&data);
	return (0);
}
