/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:00:59 by mangheli          #+#    #+#             */
/*   Updated: 2023/02/14 14:02:09 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int	ignore_chars(char *line, int index)
{
	while (line[index] != MTY_SPACE_1 && line[index] != MTY_SPACE_2 && line[index] != '\0')
	{
		index++;
	}
	return (index);
}
