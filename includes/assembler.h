/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:24:54 by marius            #+#    #+#             */
/*   Updated: 2023/02/03 09:41:58 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H

# define ASSEMBLER_H
# include "../resources_42/op.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <stdbool.h>

# define MTY_SPACE_1 ' '
# define MTY_SPACE_2 '	'

# define NULL_SEPARATOR 4

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

#endif