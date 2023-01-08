/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:23:15 by marius            #+#    #+#             */
/*   Updated: 2023/01/08 14:54:28 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

static	void	exit_ussage(void)
{
	ft_printf("Usage : ./assembler [filename]");
	exit(1);
}

// The assembler is meant to read through the .s file representing a champion
// and take the code written in assembly language and turn it in bytecode
// that the Virtual Machine can read. 
int	main (int argc, char **argv)
{
	if (argc != 2)
		exit_ussage();
	return (0);
}