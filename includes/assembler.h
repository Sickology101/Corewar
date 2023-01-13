/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:24:54 by marius            #+#    #+#             */
/*   Updated: 2023/01/13 16:54:52 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H

#define ASSEMBLER_H
# include "ft_printf.h"
# include <stdbool.h>

#define LABEL_CHAR "abcdefghijklmnopqrstuvwxyz_0123456789"

// a struct to save the arguments in planning to use it as
// a template to check against when reading, but also save 
// the statements in.
// arg type is saved as a int
// 1 = T_REG
// 2 = T_IND
// 3 = T_DIR
// when multiple types are allowed then a combination of the 3 num is used
typedef	struct s_statements
{
	char	*str;
	int		arg_num;
	int		*arg;
}				t_statements;

typedef struct	s_data
{
	t_statements	*s;
	char			**file;
	int				file_size;
}			t_data;

int		scan_file(t_data *data, int fd);
void	exit_usage(void);
void	init_statements(t_data *data);
#endif