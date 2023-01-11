/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:24:54 by marius            #+#    #+#             */
/*   Updated: 2023/01/11 16:17:42 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H

#define ASSEMBLER_H
# include "ft_printf.h"

typedef struct s_data
{
	char	**file;
	int		file_size;
}			t_data;

int scan_file(t_data *data, int fd);
void	exit_usage(void);
#endif