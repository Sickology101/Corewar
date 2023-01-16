/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:24:54 by marius            #+#    #+#             */
/*   Updated: 2023/01/16 15:10:23 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H

# define ASSEMBLER_H
# include "../resources_42/op.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <stdbool.h>

# define LABEL_CHAR "abcdefghijklmnopqrstuvwxyz_0123456789"
# define MTY_SPACE_1 " "
# define MTY_SPACE_2 "	"



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
	int					args[3]; // for live ->args[0] = 2 args[1] = 0;
 	int					opcode;
	struct s_command	*next;
}						t_command;

typedef struct s_label
{
	char	*name;
	int		number_byte;
	t_command	instruction;
}				t_label;


typedef struct s_champion
{
	char			*name;
	char			*comment;
	int				commands_nub;
	t_command		*commands;
	t_label			*labels;
	struct s_champion	*next;
}			t_champion;


typedef struct	s_parser
{
	t_statements	*s;
	char			**file;
	int				file_size;
	t_champion		*champ;
}			t_parser;

t_commmand		g_operation[17];

int		scan_file(t_parser *data, int fd);
void	exit_usage(void);
void	init_statements(t_parser *data);
void	write_bytes(int fd, int input, int count_bytes);
void	write_bytecode(t_data *data, char **argv);
#endif