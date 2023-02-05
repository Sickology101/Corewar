/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:23:44 by marius            #+#    #+#             */
/*   Updated: 2023/02/05 16:29:06 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int	search_up(t_parser *data, int index, char *label)
{
	int	size;

	size = 0;
	index--;
	while (index > 1)
	{
		size = size - data->line[index]->size;
		if (data->line[index]->type == 0 || data->line[index]->type == 2)
			if (!ft_strcmp(label, data->line[index]->label))
				return (size);
		index--;
	}
	return (0);
}

int	search_down(t_parser *data, int index, char *label)
{
	int	size;

	size = 0;
	while (index < data->file_size)
	{
		if (data->line[index]->type == 0 || data->line[index]->type == 2)
			if (!ft_strcmp(label, data->line[index]->label))
				return (size);
		size = size + data->line[index]->size;
		index++;
	}
	return (0);
}

char	*get_label_from_arg(char *str)
{
	char	*dest;
	int		index;

	dest = (char *)malloc(sizeof(char) * ft_strlen(str) - 1);
	index = 2;
	while (str[index] != '\0')
	{
		dest[index - 2] = str[index];
		index++;
	}
	dest[index - 2] = '\0';
	return (dest);
}

void	inner_calculate_dir(t_parser *data, int index, bool found)
{
	char	*label;

	found = false;
	if (data->line[index]->dir_loc[i] == 1)
	{
		label = get_label_from_arg(data->line[index]->arg[i]);
		if (data->line[index]->type == 0 || data->line[index]->type == 2)
		{
			if (!ft_strcmp(label, data->line[index]->label))
			{
				data->line[index]->arg_num[i] = 0;
				found = true;
			}
		}
		if (found == false)
		{
			data->line[index]->arg_num[i] = search_up(data, index, label);
			if (data->line[index]->arg_num[i] == 0)
				data->line[index]->arg_num[i] = search_down(data, index, label);
			if (data->line[index]->arg_num[i] == 0)
				exit_usage(7);
		}
	}
}

void	calculate_dir(t_parser *data, int index)
{
	int		i;
	bool	found;

	i = 0;
	found = false;
	while (i < 3)
	{
		inner_calculate_dir(data, index, found);
		i++;
	}	
}

void	populate_t_dir(t_parser *data)
{
	int	index;

	index = 2;
	while (index < data->file_size)
	{
		if (data->line[index]->dir_label)
			calculate_dir(data, index);
		index++;
	}
}
