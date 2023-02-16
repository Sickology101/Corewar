/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:10:24 by marius            #+#    #+#             */
/*   Updated: 2023/02/16 17:02:10 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/assembler.h"

int	search_up(t_parser *data, int index, char *label, bool *found)
{
	int	size;
	int	i;

	i = 2;
	size = 0;
	while (i < index)
	{
		if (data->line[i]->type == 0 || data->line[i]->type == 2)
		{
			if (!ft_strcmp(label, data->line[i]->label))
			{
				*found = true;
				break ;
			}
		}
		i++;
	}
	while (i < index)
	{
		size = size - data->line[i]->size;
		i++;
	}
	return (size);
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
