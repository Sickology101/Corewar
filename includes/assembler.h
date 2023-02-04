/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:24:54 by marius            #+#    #+#             */
/*   Updated: 2023/02/03 11:11:04 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H

# define ASSEMBLER_H
# include "ft_printf.h"
# include <fcntl.h>
# include <stdbool.h>

# define MTY_SPACE_1 ' '
# define MTY_SPACE_2 '	'
# define IND_SIZE 2
# define REG_SIZE 4
# define DIR_SIZE REG_SIZE
# define COMMENT_CHAR '#'
# define LABEL_CHAR ':'
# define DIRECT_CHAR '%'
# define SEPARATOR_CHAR ','
# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"
# define NULL_SEPARATOR 4
# define T_REG 1
# define T_DIR 2
# define T_IND 4
# define T_LAB 8
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct s_line
{
	char	*str;
	int		type;
	int		state_code;
	int		req_arg_num;
	int		req_arg_type[3];
	int		dir_size;
	char	*label;
	char	*statement;
	int		arg_num[3];
	bool	dir_label;
	int		dir_loc[3];
	char	**arg;
	int		arg_type[3];
	bool	arg_code_req;
	int		arg_code[8];
	int		size;
}			t_line;

typedef struct s_label
{
	char	*name;
	int		pos;
	bool	statement;
}			t_label;

typedef struct s_statements
{
	char	*name;
	int		arg_num;
	int		arg[3];
}				t_statements;

typedef struct s_parser
{
	t_line			**line;
	int				file_size;
	int				fd;
	char			*name;
	char			*comment;
	t_statements	*s;
}			t_parser;

void	scan_file(t_parser *data);
bool	ignore_comment_empty(char *line);
void	get_name_comment(t_parser *data);
void	exit_usage(int flag);
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
int		get_name_size(char *line, int index);
void	get_name(t_parser *data, char *line, int *index);
bool	check_valid_statement_name(char *str, t_parser *data);
char	*get_arg(char *line, int *index);
bool	check_valid_arg_type(t_parser *data, int flag, char *arg, int index);
int		get_number_index(char *str, int *index);
void	check_valid_reg(t_parser *data, char *arg, int flag);
void	check_valid_dir(t_parser *data, char *arg, int flag);
int		get_inst_size(t_parser *data, int state_code, int arg_code);
void	check_valid_ind(t_parser *data, char *arg, int flag);
void	handle_3_arg_2(t_parser *data, char *line, int index);
void	check_arg(t_parser *data, char *arg, int flag);
void	handle_arg_code(t_parser *data);

#endif