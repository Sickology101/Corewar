/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:50:23 by marius            #+#    #+#             */
/*   Updated: 2023/02/14 14:08:02 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int	calculate_size(char *line)
{
	int	index;
	int	size;

	index = 0;
	size = 1;
	while (line[index] != '"')
	{
		index++;
	}
	index++;
	while (line[index] != '"')
	{
		index++;
		size++;
	}
	return (size - 1);
}

void	check_size(int size, int flag)
{
	if (flag == 0)
	{
		if (size > PROG_NAME_LENGTH)
			exit_usage(1);
	}
	else
	{
		
		if (size > COMMENT_LENGTH)
			exit_usage(1);
	}
}

void	store_name_comment(t_parser *data, int flag)
{
	int		index;
	int		size;
	int		i;

	index = 0;
	size = calculate_size(data->line[flag]->str);
	check_size(size, flag);
	while (data->line[flag]->str[index] != '"')
	{
		index++;
	}
	index++;
	i = 0;
	if (flag == 0)
	{
		while (i < size)
		{
			data->name[i] = data->line[flag]->str[index];
			i++;
			index++;
		}
		data->name[i] = '\0';
	}
	else 
	{
		while (i < size)
		{
			data->comment[i] = data->line[flag]->str[index];
			i++;
			index++;
		}
		data->comment[i] = '\0';
	}
}

void	scan_file(t_parser *data)
{
	data->line = (t_line **)malloc(sizeof(t_line *) * 1064);
	get_name_comment(data);
	store_name_comment(data, 0);
	store_name_comment(data, 1);
	get_instructions(data);
}
