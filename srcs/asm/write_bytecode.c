/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytecode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:40:53 by parkharo          #+#    #+#             */
/*   Updated: 2023/01/14 14:48:37 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	write_bytecode(t_parser *data, char **av)
{
	int		i;
	t_parser	*start;

	i = 0;
	start = data;
	while (av[++i])
	{
		if (ft_strcmp(av[i], "-a"))
		{
			byte_writer(start, av[i]);
			start = start->next;
		}
	}
}