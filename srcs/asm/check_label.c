/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:45:58 by marius            #+#    #+#             */
/*   Updated: 2023/01/17 15:47:48 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

bool	check_valid_label_char(char c)
{
	int	index;

	index = 0;
	while (index < 38)
	{
		if (c == LABEL_CHARS[index])
			return (true);
		index++;
	}
	return (false);
}

char *get_label_name(char *line, int size)
{
	char *dest;
	int		index;

	dest = (char *)malloc(sizeof(char) * (size + 1));
	index = 0;
	while (index < size)
	{
		dest[index] = line[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

void	save_label(char *line, int size, t_parser *data)
{
	t_label	*temp;

	temp = data->label;
	while (temp != NULL)
	{
		temp = temp->next;
	}
	temp = (t_label *)malloc(sizeof(t_label));
	temp->name = get_label_name(line, size);
	//temp->instruction = save_instruction(line, size);
}

// checks the line and reads through the first chars up to ':'
// to see if they are valid LABEL_CHARs then checks the rest of it to see
// if it is a valid statement
bool	check_valid_label(char *line, t_parser *data)
{
	int	index;
	int	size;

	index = 0;
	while (line[index] != LABEL_CHAR)
	{
		if (!check_valid_label_char(line[index]))
			return (false);
		index++;
	}
	size = index;
	if (line[++index] != '\0')
	{
		if (line[index] == MTY_SPACE_1 || line[index] == MTY_SPACE_2)
		{
			if (!check_valid_state(line, index, data))
				exit_usage(3);
		}
		else
			exit_usage(3);
	}
	save_label(line, size, data);
	return (true);
}