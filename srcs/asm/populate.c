/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:23:44 by marius            #+#    #+#             */
/*   Updated: 2023/02/06 10:11:48 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

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
