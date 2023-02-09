/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:23:35 by marius            #+#    #+#             */
/*   Updated: 2023/02/09 17:15:37 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	exit_error_message(char *message)
{
	ft_putendl(message);
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
		printf("\033[0;93m\n NO LIVES WERE SHOUTED!\033[0m\n\n");//temporary
		while (winner->next)
			winner = winner->next;
	}
	printf("\n\033[0;32m \t WINNER IS: %s\033[0m\n", winner->name);//temporary
	ft_printf("Contestant %i, ", winner->id);
	ft_putchar('"');
	ft_printf("%s", winner->name);
	ft_putchar('"');
	ft_printf(", has won !");
}

int	main(const int ac, const char **av)
{
	t_data		data;

	init_data(&data);
	if (ac < 2)
		exit_error_message("Not enough players!");
	validate_user_input(ac, av, &data);
	validate_player(&data);
	print_champion_path_and_id(&data);
	print_introduction(&data);
	init_arena(&data);
	run_game_loop(&data);
	print_winner(&data);
	printf("\n\033[0;93m \t Game took %d loops\n\n\033[0m", data.counter.cycles_total);//temporary
	return (0);
}
