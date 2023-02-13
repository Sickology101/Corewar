/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:23:44 by marius            #+#    #+#             */
/*   Updated: 2023/02/13 10:59:59 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

char	*get_label_from_arg(char *str)
{
	char	*dest;
	int		index;
	int		i;

	dest = (char *)malloc(sizeof(char) * ft_strlen(str) - 1);
	ft_printf("\n\n STR IN GET LABEL IS '%s' \n\n", str);
	if (str[0] == '%')
		index = 2;
	else
		index = 1;
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
		ft_printf("\n\n Ldata->line[index]->type  IS '%i' \n\n", data->line[index]->type );
		if (data->line[index]->type == 0 || data->line[index]->type == 2)
		{
			ft_printf("\n\n LINE LABEL IS '%s' \n\n", data->line[index]->label);
			if (!ft_strcmp(label, data->line[index]->label))
			{
				data->line[index]->arg_num[i] = 0;
				found = true;
			}
		}
		if (found == false)
		{
			ft_printf("\n\n LABEL IS '%s' \n\n", label);
			ft_printf("\n\n data statement is '%s', data line is '%s' \n\n", data->line[index]->statement, data->line[index]->str );
			data->line[index]->arg_num[i] = search_up(data, index, label, &found);
			if (!found)
				data->line[index]->arg_num[i] = search_down(data, index, label, &found);
			if (!found)
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
