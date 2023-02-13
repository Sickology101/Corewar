/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:23:44 by marius            #+#    #+#             */
/*   Updated: 2023/02/13 16:09:21 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

char	*get_label_from_arg(char *str)
{
	char	*dest;
	int		index;
	int		i;

	if (str[0] == '%')
		index = 2;
	else
		index = 1;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(str) - (index - 1)));
	i = 0;
	while (str[index] != '\0')
	{
		dest[i] = str[index];
		i++;
		index++;
	}
	dest[i] = '\0';
	return (dest);
}

void	inner_calculate_dir(t_parser *data, int index, int i, bool found)
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
			data->line[index]->arg_num[i] = search_up(data, index, label, &found);
			if (!found)
				data->line[index]->arg_num[i] = search_down(data, index, label, &found);
			if (!found)
				exit_usage(7);
		}
		free(label);
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
		inner_calculate_dir(data, index, i, found);
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
