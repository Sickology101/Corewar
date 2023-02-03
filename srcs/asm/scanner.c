/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:50:23 by marius            #+#    #+#             */
/*   Updated: 2023/02/03 09:56:47 by marius           ###   ########.fr       */
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
	dest = (char *)malloc(sizeof(char) * size);
	dest[size - 1] = '\0';
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
