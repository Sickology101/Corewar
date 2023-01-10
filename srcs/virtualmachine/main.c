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

void	validate_magic_header(const int i, const char **av)
{
	
}

void	open_players(const int ac, const char **av)
{
	int	i;
	
	i = 1;
	while (i < ac)
	{
		validate_file_extension(i, av);
		validate_magic_header(i, av);
		i++;
	}
}

int	main(const int ac, const char **av)
{
	if (ac < 2)
		exit_error_message("Not enough players!");
	open_players(ac, av);

	return(0);
}