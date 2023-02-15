/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:00:59 by mangheli          #+#    #+#             */
/*   Updated: 2023/02/15 21:35:25 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int	ignore_chars(char *line, int i)
{
	while (line[i] != MTY_SPACE_1 && line[i] != MTY_SPACE_2 && line[i] != '\0')
	{
		i++;
	}
	return (i);
}
