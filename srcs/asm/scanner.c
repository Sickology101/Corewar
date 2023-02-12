/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:50:23 by marius            #+#    #+#             */
/*   Updated: 2023/02/12 13:44:35 by parkharo         ###   ########.fr       */
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

char	*store_name_comment(t_parser *data, int flag)
{
	int		index;
	int		size;
	char	*dest;
	int		i;

	index = 0;
	size = calculate_size(data->line[flag]->str);
	dest = ft_strnew(size);
	while (data->line[flag]->str[index] != '"')
	{
		index++;
	}
	index++;
	i = 0;
	while (i < size)
	{
		dest[i] = data->line[flag]->str[index];
		i++;
		index++;
	}
	return (dest);
}

void	scan_file(t_parser *data)
{
	data->line = (t_line **)malloc(sizeof(t_line *) * 1064);
	get_name_comment(data);
	data->name = store_name_comment(data, 0);
	data->comment = store_name_comment(data, 1);
	get_instructions(data);
}
