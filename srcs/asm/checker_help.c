/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:25:13 by marius            #+#    #+#             */
/*   Updated: 2023/01/28 03:52:21 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*// this function ignores empty lines
bool	check_empty_line(char *str)
{
	if (str[0] == '\0')
		return (true);
	else
		return (false);
}

// checks the first char of the line to see if it is a comment
bool	check_comment(char *str)
{
	if (str[0] == '#')
		return (true);
	return (false);
}

// searches for a char in the string and returns it's index
int	search_char(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index] != c && str[index] != '\0')
	{
		index++;
	}
	if (str[index] == '\0')
		return (0);
	else
		return (index);
}
*/