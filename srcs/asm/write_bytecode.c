/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytecode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:40:53 by parkharo          #+#    #+#             */
/*   Updated: 2023/02/04 13:46:31 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	write_bytecode(t_parser *data, char **av)
{
	int			i;
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
