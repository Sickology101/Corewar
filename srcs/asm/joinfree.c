/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:24:40 by parkharo          #+#    #+#             */
/*   Updated: 2023/02/04 13:47:35 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/assembler.h"

char	*join_free(char *line, char *line2, int flag)
{
	char	*line3;
	char	*line4;

	if (!line2 || !line)
		return (NULL);
	line3 = ft_strdup(line);
	line4 = ft_strdup(line2);
	ft_strdel(&line);
	line = ft_strjoin(line3, line4);
	if (flag == 1)
		ft_strdel(&line2);
	ft_strdel(&line3);
	line3 = ft_strdup(line);
	ft_strdel(&line);
	line = ft_strjoin(line3, "\n");
	ft_strdel(&line3);
	ft_strdel(&line4);
	return (line);
}
