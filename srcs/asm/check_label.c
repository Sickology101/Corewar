/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:45:58 by marius            #+#    #+#             */
/*   Updated: 2023/01/17 11:28:51 by marius           ###   ########.fr       */
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

// checks the line and reads through the first chars up to ':'
// to see if they are valid LABEL_CHARs then checks the rest of it to see
// if it is a valid statement
bool	check_valid_label(char *line, t_parser *data)
{
	int	index;

	index = 0;
	while (line[index] != LABEL_CHAR)
	{
		if (!check_valid_label_char(line[index]))
			return (false);
		index++;
	}
	if (line[++index] != '\0')
		if (!check_valid_state(line, index, data))
			exit_usage(3);
	return (true);
}