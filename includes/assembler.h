/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:24:54 by marius            #+#    #+#             */
/*   Updated: 2023/02/02 12:48:21 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H

# define ASSEMBLER_H
# include "../resources_42/op.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <stdbool.h>

//# define LABEL_CHAR "abcdefghijklmnopqrstuvwxyz_0123456789"
# define MTY_SPACE_1 ' '
# define MTY_SPACE_2 '	'

# define NULL_SEPARATOR 4
typedef	struct s_line
{
	char	*str;
	int		type; // 0 for label, 1 for statement, 2 for label and statement
	int		state_code; //saves the code for the statement (1 - 16)
	int		req_arg_num;
	int		req_arg_type[3];
	int		dir_size;
	char	*label; // saves the label 
	char	*statement; // saves the statement as char
	int		arg_num[3]; // saves the value of the argument except for label
	bool	dir_label; // true if there are T_DIR with labels
	int		dir_loc[3]; // used to know which arg is T_DIR with label
	char	**arg; // saves the arg
	int		arg_type[3]; // saves the arg type
	bool	arg_code_req; // true if arg_code is needed
	int		arg_code[8]; // saves the arg code in binary
	int		size; //saves the size of the statement
}			t_line;

typedef	struct s_label
{
	char	*name;
	int		pos;
	bool	statement;
}			t_label;

typedef	struct s_statements
{
	char	*name;
	int		arg_num;
	int		arg[3];
}				t_statements;

typedef struct	s_parser
{
	t_line	**line;
	int				file_size;
	int		fd;
	char	*name;
	char	*comment;
	t_statements	*s;
}			t_parser;

void	scan_file(t_parser *data);
bool	ignore_comment_empty(char *line);
void	get_name_comment(t_parser *data);
void	exit_usage(int	flag);
int		ignore_spaces(char *str, int index);
void	get_instructions(t_parser *data);
void	get_statement(t_parser *data, char *line, int index);
void	init_statements(t_parser *data);
void	write_to_file(t_parser *a, char **av);
void	write_bytes(int fd, int input, int count_bytes);
char	*join_free(char *line, char *line2, int flag);
void	gen_arg_code(t_parser *data);
void	populate_t_dir(t_parser *data);
int		binary_dec(int *array);

// a struct to save the arguments in planning to use it as
// a template to check against when reading, but also save 
// the statements in.
// arg type is saved as a int
// #define T_REG					1
// #define T_DIR					2
// #define T_IND					4
// #define T_LAB					8
// when multiple types are allowed then a combination of the 3 num is used
/*typedef	struct s_statements
{
	char	*str;
	int		arg_num;
	int		*arg;
	
}				t_statements;

typedef struct			s_command
{
	int					name;
	char				arg_code[8];
	char 				*label;
	int					count_args;
	int					args[3]; // for live ->args[0] = 2 args[1] = 0;
 	int					opcode;
}						t_command;

typedef struct s_label
{
	char	*name;
	int		number_byte;
	t_command	*instruction;
}				t_label;


typedef struct s_champion
{
	char			*name;
	char			*comment;
	int				commands_nub;
	t_command		**commands;
	struct s_champion	*next;
}			t_champion;

typedef	struct file
{
	char	*line;
	bool	label;
	int		size;
}			t_file;



typedef struct	s_parser
{
	t_statements	*s;
	t_file			*file;
	int				file_size;
	t_champion		*champ;
	char			**label;
	int				label_num;
}			t_parser;

t_command		g_operation[17];

int		scan_file(t_parser *data, int fd);
void	exit_usage(int flag);
void	init_statements(t_parser *data);
char	*get_name(int fd, char *line);
bool	check_comment(char *str);
bool	check_empty_line(char *str);
int	ignore_spaces(char *str, int index);
bool	get_name_comment(t_parser *data, int fd);
int		search_char(char *str, char c);
bool	check_comment(char *str);
bool	check_valid_label(char *line, t_parser *data);
bool	check_valid_label_char(char c);
bool	check_valid_state(char *line, int index, t_parser *data);
bool	compare_syntax(char *str, t_parser *data, int	*state_num);
t_champion *generate_champ(t_parser *data);
char	*get_label(char *line, int *index);
char *get_syntax_name(char *str, int *index);
//void	write_bytes(int fd, int input, int count_bytes);
//void	write_bytecode(t_parser *data, char **argv);
*/
#endif