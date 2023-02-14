/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:23:35 by marius            #+#    #+#             */
/*   Updated: 2023/02/09 19:13:29 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	exit_error_message(char *message)
{
	ft_putendl(message);
	ft_putstr("Usage:\tcorewar [-dump <num>] [-n <num>] <champion.cor> <...>\n");
	ft_putstr("\t\t-dump\t<num>\t\t : Dump memory after <num> cycles and exit\n");
	ft_putstr("\t\t-n\t<num>\t\t : Set <num> tp the next player\n");
	exit(0);
}

void	print_winner(t_data *const data)
{
	t_player	*winner;

	winner = data->player;
	if (data->last_alive)
	{
		while (winner && winner->id != (data->last_alive * -1))
			winner = winner->next;
	}
	else
	{
		while (winner->next)
			winner = winner->next;
	}
	ft_printf("Contestant %i, \"%s\", has won !\n", winner->id, winner->name);
}

int	main(const int ac, const char **av)
{
	t_data		data;

	init_data(&data);
	if (ac < 2)
		exit_error_message("Not enough players!");
	validate_user_input(ac, av, &data);
	validate_player(&data);
	print_introduction(&data);
	init_arena(&data);
	run_game_loop(&data);
	print_winner(&data);
	return (0);
}
