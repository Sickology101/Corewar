/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:13:28 by marius            #+#    #+#             */
/*   Updated: 2023/02/06 10:15:06 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	writing_command2(int fd, t_parser *a, int index)
{
	int	i;

	write_bytes(fd, a->line[index]->state_code, 1);
	if (a->line[index]->arg_code_req == true)
		write_bytes(fd, binary_dec(a->line[index]->arg_code), 1);
	i = 0;
	while (i < a->line[index]->req_arg_num)
	{
		if (a->line[index]->arg_type[i] == 1)
			write_bytes(fd, a->line[index]->arg_num[i], 1);
		else if (a->line[index]->arg_type[i] == 4)
			write_bytes(fd, a->line[index]->arg_num[i], 2);
		else
		{
			write_bytes(fd, a->line[index]->arg_num[i],
				a->line[index]->dir_size);
		}
		i++;
	}
}

void	writing_command(int fd, t_parser *a)
{
	int	index;

	index = 2;
	while (index < a->file_size)
	{
		if (a->line[index]->size != 0)
		{
			writing_command2(fd, a, index);
		}
		index++;
	}
}
