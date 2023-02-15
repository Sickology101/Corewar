/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:13:28 by marius            #+#    #+#             */
/*   Updated: 2023/02/15 21:31:02 by parkharo         ###   ########.fr       */
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

int	ft_strnccmp(char *line)
{
	int	index;

	while (*line == MTY_SPACE_1 || *line == MTY_SPACE_2)
	{
		++line;
	}
	if (ft_strncmp(line, ".name", 5) == 0)
	{
		index = 5;
		index = ignore_spaces(line, index);
		if (line[index] != '"')
			exit_usage(1);
		return (1);
	}
	if (ft_strncmp(line, ".comment", 8) == 0)
	{
		index = 8;
		index = ignore_spaces(line, index);
		if (line[index] != '"')
			exit_usage(1);
		return (2);
	}
	return (0);
}
