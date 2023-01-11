/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:50:23 by marius            #+#    #+#             */
/*   Updated: 2023/01/11 13:44:58 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"


//a function that reads through the file and checks the syntax
//returns 1 if an error was found
int scan_file(t_data *data, int fd)
{
	int ret;
	char *line;

	data->file_size = 0;
	ret = get_next_line(fd, &line);
	data->file = (char **)malloc(sizeof(char *) * 2);
	data->file[0] = ft_strdup(line);
	if (ret == -1 || ret == 0)
		return (1);
	ret = get_next_line(fd, &line);
	data->file[1] = ft_strdup(line);
	if (ret == -1 || ret == 0)
		return (1);
	return (0);
}