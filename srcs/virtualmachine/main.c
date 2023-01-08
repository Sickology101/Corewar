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

void	exit_error_message(char *message, int status)
{
	ft_putendl(message);
	exit(status);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		exit_error_message("Not enough players!", 0);
	return(0);
}