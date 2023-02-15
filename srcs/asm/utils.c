/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:02:13 by parkharo          #+#    #+#             */
/*   Updated: 2023/02/05 15:50:22 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/assembler.h"

void	set_some_arg_shit(t_parser *data, int index1, int index2)
{
	if (data->line[data->file_size]->arg_type[index2] == 1)
	{
		data->line[data->file_size]->arg_code[index1] = 0;
		data->line[data->file_size]->arg_code[index1 + 1] = 1;
	}
	else if (data->line[data->file_size]->arg_type[index2] == 2)
	{
		data->line[data->file_size]->arg_code[index1] = 1;
		data->line[data->file_size]->arg_code[index1 + 1] = 0;
	}
	else
	{
		data->line[data->file_size]->arg_code[index1] = 1;
		data->line[data->file_size]->arg_code[index1 + 1] = 1;
	}
}

void	gen_arg_code(t_parser *data)
{
	int	index1;
	int	index2;

	index1 = 0;
	index2 = 0;
	while (index1 < 8)
	{
		while (index2 < data->line[data->file_size]->req_arg_num)
		{
			set_some_arg_shit(data, index1, index2);
			index1 += 2;
			index2++;
		}
		data->line[data->file_size]->arg_code[index1] = 0;
		index1++;
	}
}

int	ignore_spaces(char *s, int i)
{
	while (s[i] != '\0' && (s[i] == MTY_SPACE_1 || s[i] == MTY_SPACE_2))
	{
		i++;
	}
	return (i);
}

bool	ignore_comment_empty(char *line)
{
	int	index;

	index = 0;
	while (line[index] != '\0')
	{
		if (line[index] == COMMENT_CHAR)
			return (true);
		if (line[index] != MTY_SPACE_1 && line[index] != MTY_SPACE_2)
			return (false);
		index++;
	}
	return (true);
}

int	binary_dec(int *array)
{
	int	decimal_num;
	int	index;
	int	base;

	index = 7;
	base = 1;
	decimal_num = 0;
	while (index >= 0)
	{
		decimal_num = decimal_num + array[index] * base;
		base = base * 2;
		index--;
	}
	return (decimal_num);
}

/*t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

char	**get_champ_name(void)
{
	t_data	*data;

	data = get_data();
	return (&data->file[0]);	
}

char **get_comment(void)
{
	t_data	*data;

	data = get_data();
	return (&data->file[1]);	
}


void	populate_data(void)
{
	char	*line;
	int ret = ft_getnextline(fd, 1818238, &line);

	get_data()->name = line;
}

void	update_champ(t_champion *champ)
{
	champ->name = ft_strdup(get_champ_name());
}

char	*join_free(char *line, char *line2, int flag)
{
	char	*line3;
	char	*line4;

	if (!line2 || !line)
		return (NULL);
	line3 = ft_strdup(line);
	line4 = ft_strdup(line2);
	ft_strdel(&line);
	line = ft_strjoin(line3, line4);
	if (flag == 1)
		ft_strdel(&line2);
	ft_strdel(&line3);
	line3 = ft_strdup(line);
	ft_strdel(&line);
	line = ft_strjoin(line3, "\n");
	ft_strdel(&line3);
	ft_strdel(&line4);
	return (line);
}

int		size_code(t_champion *a)
{
	int			size;
	t_command	*command;
	t_arg		*arg;

	size = 0;
	command = a->cmds;
	while (command)
	{
		if (ft_strcmp(command->name, "-1"))
		{
			size++;
			if (command->codage)
				size++;
			arg = command->inst;
			while (arg)
			{
				size += arg->size;
				arg = arg->next;
			}
		}
		command = command->next;
	}
	return (size);
}
*/