/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_statements3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:21:59 by marius            #+#    #+#             */
/*   Updated: 2023/02/16 17:24:38 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/assembler.h"

long long	get_number_index(char *str, int *index)
{
	char	*number;
	int		i;
	int		n;

	number = (char *)malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	if (str[*index] == '-')
	{
		number[i++] = str[*index];
		*index += 1;
	}
	while (ft_isdigit(str[*index]))
	{
		number[i] = str[*index];
		i++;
		*index = *index + 1;
	}
	number[i] = '\0';
	n = ft_atoi(number);
	free(number);
	return (n);
}

void	check_valid_reg(t_parser *data, char *arg, int flag)
{
	int	index;

	index = 1;
	if (arg[0] != 'r')
		exit_usage(4);
	if (!ft_isdigit(arg[1]))
		exit_usage(4);
	data->line[data->file_size]->arg_num[flag] = get_number_index(arg, &index);
	index = ignore_spaces(arg, index);
	if (arg[index] != SEPARATOR_CHAR && arg[index] != COMMENT_CHAR
		&& arg[index] != '\0')
		exit_usage(4);
	data->line[data->file_size]->arg[flag] = ft_strdup(arg);
}

void	check_valid_dir(t_parser *data, char *arg, int flag)
{
	int	index;

	index = 1;
	if (arg[0] != '%')
		exit_usage(4);
	if (arg[1] == ':')
	{
		data->line[data->file_size]->arg[flag] = ft_strdup(arg);
		data->line[data->file_size]->dir_label = true;
		data->line[data->file_size]->dir_loc[flag] = 1;
	}
	else if (!ft_isdigit(arg[index]) && arg[index] != '-')
		exit_usage(4);
	else
	{
		data->line[data->file_size]->arg_num[flag]
			= get_number_index(arg, &index);
		index = ignore_spaces(arg, index);
		if (arg[index] != SEPARATOR_CHAR && arg[index]
			!= COMMENT_CHAR && arg[index] != '\0')
			exit_usage(4);
		data->line[data->file_size]->arg[flag] = ft_strdup(arg);
	}
}

int	get_inst_size(t_parser *data, int state_code, int arg_code)
{
	if (arg_code == 1)
		return (1);
	if (arg_code == 4)
		return (2);
	if (arg_code == 2)
	{
		if ((state_code > 8 && state_code < 13)
			|| state_code == 14 || state_code == 15)
		{
			data->line[data->file_size]->dir_size = 2;
			return (2);
		}
		else
		{
			data->line[data->file_size]->dir_size = 4;
			return (4);
		}
	}
	return (0);
}

void	check_valid_ind(t_parser *data, char *arg, int f)
{
	int	index;

	index = 0;
	if (arg[0] == ':')
	{
		data->line[data->file_size]->arg[f] = ft_strdup(arg);
		data->line[data->file_size]->dir_label = true;
		data->line[data->file_size]->dir_loc[f] = 1;
	}
	else
	{
		if (!ft_isdigit(arg[index]) && arg[index] != '-')
			exit_usage(4);
		data->line[data->file_size]->arg_num[f] = get_number_index(arg, &index);
		index = ignore_spaces(arg, index);
		if (arg[index] != SEPARATOR_CHAR && arg[index]
			!= COMMENT_CHAR && arg[index] != '\0')
			exit_usage(4);
		data->line[data->file_size]->arg[f] = ft_strdup(arg);
	}
}
