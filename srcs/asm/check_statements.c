/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_statements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:30:08 by marius            #+#    #+#             */
/*   Updated: 2023/01/17 11:36:15 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

char *get_syntax_name(char *str, int *index)
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
bool	check_valid_reg(char *str, int index)
{
	if (str[index] != 'r')
		return (false);
	index++;
	while (ft_isdigit(str[index]))
	{
		index++;
	}
	if (str[index] == MTY_SPACE_1 || str[index] == MTY_SPACE_2 || str[index] == '\0' || str[index] == '#' || str[index] == ',')
		return (true);
	return (false);
}

bool	check_valid_dir(char *str, int index)
{
	if (str[index++] != '%')
		return (false);
	if (str[index++] == LABEL_CHAR)
	{
		while (str[index] != MTY_SPACE_1 && str[index] != MTY_SPACE_2 && str[index] != '\0' && str[index] != ',')
		{
			if (check_valid_label_char(str[index]))
				return (false);
			index++;
		}
	}
	else
	{
		while (ft_isdigit(str[index]))
		{
			index++;
		}
		if (str[index] == MTY_SPACE_1 || str[index] == MTY_SPACE_2 || str[index] == '\0' || str[index] == ',')
			return (true);
		else
			return (false);
	}
	return (true);
}

bool	check_valid_ind(char *str, int index)
{
	if (str[index++] == ':')
	{
		while (str[index] != MTY_SPACE_1 && str[index] != MTY_SPACE_2 && str[index] != '\0' && str[index] != ',')
		{
			if (check_valid_label_char(str[index]))
				return (false);
			index++;
		}
	}
	else
	{
		while (ft_isdigit(str[index]))
		{
			index++;
		}
		if (str[index] == MTY_SPACE_1 || str[index] == MTY_SPACE_2 || str[index] == '\0' || str[index] == ',')
			return (true);
		else
			return (false);
	}
	return (true);
}

// takes in the string and the index of where the arg start, the expected arg, and the predefined statement to 
// check against returns true if the arg is valid and false if not
bool	check_arg_type(char *str, int index, int arg, t_statements s)
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

bool	check_1_arg(t_statements s, char *str, int index)
{
	index = ignore_spaces(str, index);
	check_arg_type(str, index, 0, s);
	return (true);
}

bool	check_2_arg(t_statements s, char *str, int index)
{
	index = ignore_spaces(str, index);
	check_arg_type(str, index, 0, s);
	index = ignore_spaces(str, index);
	check_arg_type(str, index, 1, s);
	return (true);
}

bool	check_3_arg(t_statements s, char *str, int index)
{
	index = ignore_spaces(str, index);
	check_arg_type(str, index, 0, s);
	index = ignore_spaces(str, index);
	check_arg_type(str, index, 1, s);
	index = ignore_spaces(str, index);
	check_arg_type(str, index, 1, s);
	return (true);
}


bool	check_args(char *str, int index, int state_num, t_parser *data)
{
	index = ignore_spaces(str, index);
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
	
	while (line[index] != '\n')
	{
		while ((line[index] == MTY_SPACE_1 || line[index] == MTY_SPACE_2) && line[index] != '\0')
		{
			index++;
		}
		if (!compare_syntax(get_syntax_name(line, &index), data, &state_num))
			return (false);
		if (!check_args(line,index, state_num, data))
			return (false);
	}
	return (true);
}