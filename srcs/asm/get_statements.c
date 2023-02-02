/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_statements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:30:08 by marius            #+#    #+#             */
/*   Updated: 2023/02/02 10:58:41 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include <stdio.h>

t_statements g_operations[17] = 
{
	{"live", 1, {T_DIR, 0, 0}},
	{"ld", 2, {T_DIR + T_IND, T_REG, 0}},
	{"st",2, {T_REG, T_REG + T_IND}},
	{"add", 3, {T_REG, T_REG, T_REG}},
	{"sub", 3, {T_REG, T_REG, T_REG}},
	{"and", 3, {T_REG + T_DIR + T_IND, T_REG + T_DIR + T_IND, T_REG}},
	{"or", 3, {T_REG + T_DIR + T_IND, T_REG + T_DIR + T_IND, T_REG}},
	{"xor", 3, {T_REG + T_DIR + T_IND, T_REG + T_DIR + T_IND, T_REG}},
	{"zjmp", 1, {T_DIR, 0, 0}},
	{"ldi", 3, {T_REG + T_DIR + T_IND, T_REG + T_DIR, T_REG}},
	{"sti", 3, {T_REG, T_REG + T_DIR + T_IND, T_REG + T_DIR}},
	{"fork", 1, {T_DIR, 0, 0}},
	{"lld", 2, {T_DIR + T_IND, T_REG, 0}},
	{"lldi", 3, {T_REG + T_DIR + T_IND, T_REG + T_DIR, T_REG}},
	{"lfork", 1, {T_DIR, 0, 0}},
	{"aff", 1, {T_REG, 0, 0}},
	{NULL, 0, {0, 0, 0}}
};

int	get_name_size(char *line, int index)
{
	int	size;

	size = 0;
	while (line[index] != MTY_SPACE_1 && line[index] != MTY_SPACE_2 && line[index] != '\0' && line[index] != SEPARATOR_CHAR)
	{
		size++;
		index++;
	}
	return (size);
}

void	get_name(t_parser *data, char *line, int *index)
{
	int	size;
	int	i;

	size = get_name_size(line, *index);
	data->line[data->file_size]->statement = (char *)malloc(sizeof(char) * size);
	data->line[data->file_size]->statement[size] = '\0';
	i = 0;
	while (i < size)
	{
		data->line[data->file_size]->statement[i] = line[*index];
		i++;
		*index = *index + 1;
	}
}

bool	check_valid_statement_name(char *str, t_parser *data)
{
	int	index;

	index = 0;
	while (index < 16)
	{
		if (!ft_strcmp(str, g_operations[index].name))
		{
			data->line[data->file_size]->state_code = index + 1;
			data->line[data->file_size]->req_arg_num = g_operations[index].arg_num;
			data->line[data->file_size]->req_arg_type[0] = g_operations[index].arg[0];
			data->line[data->file_size]->req_arg_type[1] =	g_operations[index].arg[1];
			data->line[data->file_size]->req_arg_type[2] = g_operations[index].arg[2];
			
			return (true);
		}
		index++;
	}
	return (false);
}

char *get_arg(char *line, int *index)
{
	char *dest;
	int	size;
	int	i;

	size = get_name_size(line, *index);
	if (line[*index + size - 1] == SEPARATOR_CHAR)
		size--;
	i = 0;
	dest = (char *)malloc(sizeof(char) * size);
	dest[size] = '\0';
	while (i < size)
	{
		dest[i] = line[*index];
		i++;
		*index = *index + 1;
	}
	return (dest);
}

bool check_valid_arg_type(t_parser *data, int flag, char *arg, int index)
{
	int	arg_type;
	
	if (arg[0] == 'r')
		data->line[data->file_size]->arg_type[index] = 1;
	else if (arg[0] == '%')
		data->line[data->file_size]->arg_type[index] = 2;
	else
		data->line[data->file_size]->arg_type[index] = 4;
	arg_type = data->line[data->file_size]->arg_type[index];
	if (arg_type == flag)
		return (true);
	if (flag == 3)
		if (arg_type == 1 || arg_type == 2)
			return (true);
	if (flag == 5)
		if (arg_type == 1 || arg_type == 4)
			return (true);
	if (flag == 6)
		if (arg_type == 2 || arg_type == 4)
			return (true);
	if (flag == 7)
		return (true);
	return (false);
}

int	get_number_index(char *str, int *index)
{
	int n;
	int	sign;

	n = 0;
	if (str[*index] == '-')
	{
		sign = -1;
		*index = *index + 1;
	}
	else
		sign = 1;
	while (str[*index] != MTY_SPACE_1 && str[*index] != MTY_SPACE_2 && str[*index] != '\0')
	{
		if (ft_isdigit(str[*index]))
			n = n * 10 + (str[*index] - '0');
		else
			break;
		*index = *index + 1;
	}
	return (n * sign);
}

void	check_valid_reg(t_parser *data, char *arg, int flag)
{
	int	index;

	index = 1;
	if (arg[0] != 'r')
		exit_usage(4);
	if(!ft_isdigit(arg[1]))
		exit_usage(4);
	data->line[data->file_size]->arg_num[flag] = get_number_index(arg, &index);
	index = ignore_spaces(arg, index);
	if (arg[index] != SEPARATOR_CHAR && arg[index] != COMMENT_CHAR && arg[index] != '\0')
		exit_usage(4);
	data->line[data->file_size]->arg[flag] = ft_strdup(arg);
}

void	check_valid_dir(t_parser *data, char *arg, int flag)
{
	int	index;
	
	index = 1;
	if (arg[1] == '-')
		index = 2;
	if (arg[0] != '%')
		exit_usage(4);
	if (arg[1] == ':')
	{
		data->line[data->file_size]->arg[flag] = ft_strdup(arg);
		data->line[data->file_size]->dir_label = true;
		data->line[data->file_size]->dir_loc[flag] = 1;
	}
	else if (!ft_isdigit(arg[index]))
		exit_usage(4);
	else
	{
		data->line[data->file_size]->arg_num[flag] = get_number_index(arg, &index);
		index = ignore_spaces(arg, index);
		if (arg[index] != SEPARATOR_CHAR && arg[index] != COMMENT_CHAR && arg[index] != '\0')
			exit_usage(4);
		data->line[data->file_size]->arg[flag] = ft_strdup(arg);
	}
}

int	get_inst_size(int state_code, int arg_code)
{
	if (arg_code == 1)
		return (1);
	if (arg_code == 4)
		return (2);
	if (arg_code == 2)
	{
		if ((state_code > 8 && state_code < 13) || state_code == 14 || state_code == 15)
			return (2);
		else
			return (4);
	}
	return (0);
}

void	check_valid_ind(t_parser *data, char *arg, int flag)
{
	int	index;

	index = 0;
	if (arg[index] == '-')
		index++;
	if (!ft_isdigit(arg[index]))
		exit_usage(4);
	data->line[data->file_size]->arg_num[flag] = get_number_index(arg, &index);
	index = ignore_spaces(arg, index);
	if (arg[index] != SEPARATOR_CHAR && arg[index] != COMMENT_CHAR && arg[index] != '\0')
		exit_usage(4);
	data->line[data->file_size]->arg[flag] = ft_strdup(arg);
}

void	handle_1_arg(t_parser *data, char *line, int index)
{
	char *arg;

	arg = get_arg(line, &index);
	data->line[data->file_size]->arg = (char **)malloc(sizeof(char *));
	if (!check_valid_arg_type(data, data->line[data->file_size]->req_arg_type[0], arg, 0))
		exit_usage(4);
	if (data->line[data->file_size]->arg_type[0] == 1)
		check_valid_reg(data, arg, 0);
	else if (data->line[data->file_size]->arg_type[0] == 2)
		check_valid_dir(data, arg, 0);
	else
		check_valid_ind(data, arg, 0);
	index = ignore_spaces(line, index);
	if (line[index] != '\0' && line[index] != COMMENT_CHAR)
		exit_usage(4);
	data->line[data->file_size]->size = get_inst_size(data->line[data->file_size]->state_code, data->line[data->file_size]->arg_type[0]);
}

void	handle_2_arg(t_parser *data, char *line, int index)
{
	char	*arg;
	
	arg = get_arg(line, &index);
	data->line[data->file_size]->arg = (char **)malloc(sizeof(char *) * 2);
	if (!check_valid_arg_type(data, data->line[data->file_size]->req_arg_type[0], arg, 0))
		exit_usage(4);
	if (data->line[data->file_size]->arg_type[0] == 1)
		check_valid_reg(data, arg, 0);
	else if (data->line[data->file_size]->arg_type[0] == 2)
		check_valid_dir(data, arg, 0);
	else
		check_valid_ind(data, arg, 0);
	if (line[index] == SEPARATOR_CHAR)
		index++;
	else
		exit_usage(4);
	index = ignore_spaces(line, index);
	data->line[data->file_size]->size = get_inst_size(data->line[data->file_size]->state_code, data->line[data->file_size]->arg_type[0]);
	free(arg);
	arg = get_arg(line, &index);
	if (!check_valid_arg_type(data, data->line[data->file_size]->req_arg_type[1], arg, 1))
		exit_usage(4);
	if (data->line[data->file_size]->arg_type[1] == 1)
		check_valid_reg(data, arg, 1);
	else if (data->line[data->file_size]->arg_type[1] == 2)
		check_valid_dir(data, arg, 1);
	else
		check_valid_ind(data, arg, 1);
	index = ignore_spaces(line, index);
	if (line[index] != '\0' && line[index] != COMMENT_CHAR)
		exit_usage(4);
	data->line[data->file_size]->size = data->line[data->file_size]->size + get_inst_size(data->line[data->file_size]->state_code, data->line[data->file_size]->arg_type[1]);
}

void	handle_3_arg(t_parser *data, char *line, int index)
{
	char	*arg;
	
	arg = get_arg(line, &index);
	data->line[data->file_size]->arg = (char **)malloc(sizeof(char *) * 3);
	if (!check_valid_arg_type(data, data->line[data->file_size]->req_arg_type[0], arg, 0))
		exit_usage(4);
	if (data->line[data->file_size]->arg_type[0] == 1)
		check_valid_reg(data, arg, 0);
	else if (data->line[data->file_size]->arg_type[0] == 2)
		check_valid_dir(data, arg, 0);
	else
		check_valid_ind(data, arg, 0);
	if (line[index] == SEPARATOR_CHAR)
		index++;
	else
		exit_usage(4);
	index = ignore_spaces(line, index);
	data->line[data->file_size]->size = get_inst_size(data->line[data->file_size]->state_code, data->line[data->file_size]->arg_type[0]);
	free(arg);
	arg = get_arg(line, &index);
	if (!check_valid_arg_type(data, data->line[data->file_size]->req_arg_type[1], arg, 1))
		exit_usage(4);
	if (data->line[data->file_size]->arg_type[1] == 1)
		check_valid_reg(data, arg, 1);
	else if (data->line[data->file_size]->arg_type[1] == 2)
		check_valid_dir(data, arg, 1);
	else
		check_valid_ind(data, arg, 1);
	if (line[index] == SEPARATOR_CHAR)
		index++;
	else
		exit_usage(4);
	index = ignore_spaces(line, index);
	data->line[data->file_size]->size = data->line[data->file_size]->size + get_inst_size(data->line[data->file_size]->state_code, data->line[data->file_size]->arg_type[1]);
	free(arg);
	arg = get_arg(line, &index);
	if (!check_valid_arg_type(data, data->line[data->file_size]->req_arg_type[2], arg, 2))
		exit_usage(4);
	if (data->line[data->file_size]->arg_type[2] == 1)
		check_valid_reg(data, arg, 2);
	else if (data->line[data->file_size]->arg_type[2] == 2)
		check_valid_dir(data, arg, 2);
	else
		check_valid_ind(data, arg, 2);
	index = ignore_spaces(line, index);
	if (line[index] != '\0' && line[index] != COMMENT_CHAR)
		exit_usage(4);
	data->line[data->file_size]->size = data->line[data->file_size]->size + get_inst_size(data->line[data->file_size]->state_code, data->line[data->file_size]->arg_type[2]);
}

void	get_statement(t_parser *data, char *line, int index)
{
	get_name(data,line, &index);
	if (!check_valid_statement_name(data->line[data->file_size]->statement, data))
		exit_usage(3);
	index = ignore_spaces(line, index);
	data->line[data->file_size]->dir_loc[0] = 0;
	data->line[data->file_size]->dir_loc[1] = 0;
	data->line[data->file_size]->dir_loc[2] = 0;
	if (line[index] == '\0')
		exit_usage(4);
	if (data->line[data->file_size]->req_arg_num == 1)
		handle_1_arg(data, line, index);
	else if (data->line[data->file_size]->req_arg_num == 2)
		handle_2_arg(data, line, index);
	else
		handle_3_arg(data,line, index);
	if (data->line[data->file_size]->state_code == 1 || data->line[data->file_size]->state_code == 9 || data->line[data->file_size]->state_code == 12 || data->line[data->file_size]->state_code == 15)
		data->line[data->file_size]->arg_code_req = false;
	else
	{
		gen_arg_code(data);
		data->line[data->file_size]->arg_code_req = true;
		data->line[data->file_size]->size++;
	}
	data->line[data->file_size]->size++;
	//ft_printf("%x %d %d %d %d\n", data->line[data->file_size]->state_code , data->line[data->file_size]->req_arg_num, data->line[data->file_size]->req_arg_type[0], data->line[data->file_size]->req_arg_type[1], data->line[data->file_size]->req_arg_type[2]);
}

/*char *get_syntax_name(char *str, int *index)
{
	char	*dest;
	int		size;
	int		i;
	int		i2;

	size = 0;
	i = *index;
	while (str[*index] != '\0' && str[*index] != MTY_SPACE_1 && str[*index] != MTY_SPACE_2)
	{
		size++;
		(*index)++;
	}
	dest = (char *)malloc(sizeof(char) * (size + 1));
	i2 = 0;
	while (i2 < size)
	{
		dest[i2] = str[i];
		i2++;
		i++;
	}
	dest[i2] = '\0';
	return (dest);
}

bool	compare_syntax(char *str, t_parser *data, int	*state_num)
{
	int	index;

	index = 0;
	while (index < 16)
	{
		if (!ft_strcmp (str,data->s[index].str))
		{
			*state_num = index;
			return (true);
		}
		index++;
	}
	return (false);
}

// following functions will check if the args are correct lexycally
bool	check_valid_reg(char *str, int *index)
{
	if (str[*index] != 'r')
		return (false);
	*index = *index + 1;
	while (ft_isdigit(str[*index]))
	{
		*index = *index + 1;
	}
	if (str[*index] == MTY_SPACE_1 || str[*index] == MTY_SPACE_2 || str[*index] == '\0' || str[*index] == '#' || str[*index] == ',')
		return (true);
	return (false);
}

bool	check_valid_dir(char *str, int *index)
{
	if (str[*index] != '%')
		return (false);
	*index = *index + 1;
	if (str[*index] == LABEL_CHAR)
	{
		*index = *index + 1;
		while (str[*index] != MTY_SPACE_1 && str[*index] != MTY_SPACE_2 && str[*index] != '\0' && str[*index] != ',')
		{
			if (!check_valid_label_char(str[*index]))
				return (false);
			*index = *index + 1;
		}
	}
	else
	{
		if (str[*index] == '-')
			*index = *index + 1;
		while (ft_isdigit(str[*index]))
		{
			*index = *index + 1;;
		}
		if (str[*index] == MTY_SPACE_1 || str[*index] == MTY_SPACE_2 || str[*index] == '\0' || str[*index] == ',')
			return (true);
		else
			return (false);
	}
	return (true);
}

bool	check_valid_ind(char *str, int *index)
{
	if (str[*index] == ':')
	{
		*index = *index + 1;
		while (str[*index] != MTY_SPACE_1 && str[*index] != MTY_SPACE_2 && str[*index] != '\0' && str[*index] != ',')
		{
			if (check_valid_label_char(str[*index]))
				return (false);
			*index = *index + 1;
		}
	}
	else
	{
		if (str[*index] == '-')
			*index = *index + 1;
		while (ft_isdigit(str[*index]))
		{
			*index = *index + 1;
		}
		if (str[*index] == MTY_SPACE_1 || str[*index] == MTY_SPACE_2 || str[*index] == '\0' || str[*index] == ',')
			return (true);
		else
			return (false);
	}
	return (true);
}

// takes in the string and the index of where the arg start, the expected arg, and the predefined statement to 
// check against returns true if the arg is valid and false if not
bool	check_arg_type(char *str, int *index, int arg, t_statements s)
{
	if (s.arg[arg] == 1)
	{
		if (check_valid_reg(str, index))
			return (true);
	}
	else if (s.arg[arg] == 2)
	{
		if (check_valid_dir(str, index))
			return (true);
	}
	else if (s.arg[arg]== 3)
	{
		if (check_valid_reg(str, index) || check_valid_dir(str, index))
			return (true);
	}
	else if (s.arg[arg] == 4)
	{
		if (check_valid_ind(str, index))
			return (true);
	}
	else if (s.arg[arg] == 5)
	{
		if (check_valid_reg(str, index) || check_valid_ind(str, index))
			return (true);
	}
	else if (s.arg[arg] == 6)
	{
		if (check_valid_ind(str, index) || check_valid_dir(str, index))
			return (true);
	}
	else if (s.arg[arg] == 7)
	{
		if (check_valid_reg(str, index) || check_valid_dir(str, index) || check_valid_ind(str, index))
			return (true);
	}
	return (false);
}

bool	check_1_arg(t_statements s, char *str, int *index)
{
	if (check_arg_type(str, index, 0, s))
		return (true);
	else
		return (false);
}

bool	check_2_arg(t_statements s, char *str, int *index)
{
	*index = ignore_spaces(str, *index);
	if (!check_arg_type(str, index, 0, s))
		return (false);
	if (str[*index] == SEPARATOR_CHAR)
		*index = *index + 1;
	else
		return (false);
	*index = ignore_spaces(str, *index);
	if (!check_arg_type(str, index, 1, s))
		return (false);
	return (true);
}

bool	check_3_arg(t_statements s, char *str, int *index)
{
	*index = ignore_spaces(str, *index);
	if (!check_arg_type(str, index, 0, s))
		return (false);
	if (str[*index] == SEPARATOR_CHAR)
		*index = *index + 1;
	else
		return (false);
	*index = ignore_spaces(str, *index);
	if (!check_arg_type(str, index, 1, s))
		return (false);
	if (str[*index] == SEPARATOR_CHAR)
		*index = *index + 1;
	else
		return (false);
	*index = ignore_spaces(str, *index);
	if (!check_arg_type(str, index, 2, s))
		return (false);
	return (true);
}


bool	check_args(char *str, int *index, int state_num, t_parser *data)
{
	if (data->s[state_num].arg_num == 1)
	{
		if (check_1_arg(data->s[state_num], str, index))
			return (true);
	}
	else if (data->s[state_num].arg_num == 2)
	{
		if (check_2_arg(data->s[state_num], str, index))
			return (true);
	}
	else if (data->s[state_num].arg_num == 3)
	{
		if (check_3_arg(data->s[state_num], str, index))
			return (true);
	}
	return (false);
}

// checks the line from index (0 for statement line)
// to see if it follows a valid statement (name, argnumb, and arg type)
bool	check_valid_state(char *line, int index, t_parser *data)
{
	int	state_num;
	while (line[index] != '\0')
	{
		index = ignore_spaces(line, index);
		if (!compare_syntax(get_syntax_name(line, &index), data, &state_num))
			return (false);
		index = ignore_spaces(line, index);
		if (!check_args(line,&index, state_num, data))
			return (false);
		index = ignore_spaces(line, index);
		if (line[index] == '\0' || line[index] == COMMENT_CHAR)
			break;
	}
	return (true);
}
*/