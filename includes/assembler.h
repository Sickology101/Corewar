/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:24:54 by marius            #+#    #+#             */
/*   Updated: 2023/01/14 17:02:40 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H

#define ASSEMBLER_H
# include "../resources_42/op.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <stdbool.h>

#define LABEL_CHAR "abcdefghijklmnopqrstuvwxyz_0123456789"

// a struct to save the arguments in planning to use it as
// a template to check against when reading, but also save 
// the statements in.
// arg type is saved as a int
// #define T_REG					1
// #define T_DIR					2
// #define T_IND					4
// #define T_LAB					8
// when multiple types are allowed then a combination of the 3 num is used
typedef	struct s_statements
{
	char	*str;
	int		arg_num;
	int		*arg;
}				t_statements;

typedef struct			s_command
{
	char				*name;
	int					codage;
	int					count_args;
	int					label_size;
	int					args[3];
	int					opcode;
	t_label				*labels;
	int					number_byte;
	t_arg				*inst;
	struct s_command	*next;
}						t_command;

typedef struct s_champion
{
	char			*name;
	char			*comment;
	t_command		*commands;
	struct s_champion	*next;
}			t_champion;


typedef struct	s_data
{
	t_statements	*s;
	char			**file;
	int				file_size;
	t_champion		*champ;
}			t_data;

t_commmand		g_operation[17];

int		scan_file(t_data *data, int fd);
void	exit_usage(void);
void	init_statements(t_data *data);
void	write_bytes(int fd, int input, int count_bytes);
void	write_bytecode(t_data *data, char **argv);
char	*join_free(char *line, char *line2, int flag);
#endif