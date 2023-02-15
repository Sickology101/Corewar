/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:10:24 by marius            #+#    #+#             */
/*   Updated: 2023/02/15 21:28:39 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int	search_up(t_parser *data, int index, char *label, bool *found)
{
	int	size;

	size = 0;
	index--;
	while (index > 1)
	{
		size = size - data->line[index]->size;
		if (data->line[index]->type == 0 || data->line[index]->type == 2)
		{
			if (!ft_strcmp(label, data->line[index]->label))
			{
				*found = true;
				return (size);
			}
		}
		index--;
	}
	return (0);
}

int	search_down(t_parser *data, int index, char *label, bool *found)
{
	int	size;

	size = 0;
	while (index < data->file_size)
	{
		if (data->line[index]->type == 0 || data->line[index]->type == 2)
		{
			if (!ft_strcmp(label, data->line[index]->label))
			{
				*found = true;
				return (size);
			}
		}
		size = size + data->line[index]->size;
		index++;
	}
	return (0);
}
