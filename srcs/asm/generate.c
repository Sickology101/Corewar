/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:15:45 by marius            #+#    #+#             */
/*   Updated: 2023/01/28 03:52:36 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*static	int	get_size(char *str, int index)
{
	int size;

	size = 0;
	while (str[index] != '"')
	{
		size++;
		index++;
	}
	return (size);
}

static char *get_champ_name_comm(char *str)
{
	char *dest;
	int	index;
	int	i;
	int	size;

	index = 0;
	while (str[index] != '"')
	{
		index++;
	}
	index++;
	i = 0;
	size = get_size(str, index);
	dest = (char *)malloc(sizeof(char) * size);
	dest[size] = '\0';
	while (str[index] != '"')
	{
		dest[i] = str[index];
		i++;
		index++;
	}
	return (dest);
}

int	get_inst_code(char *str, int **index)
{
	char *state;

	state = get_syntax_name(str, index);
	if (!ft_strcmp(state, "live"))
		return(0x01);
	else if(!ft_strcmp(state, "ld"))
		return (0x02);
	else if (!ft_strcmp(state, "st"))
		return (0x03);
	else if (!ft_strcmp(state, "add"))
		return (0x04);
	else if (!ft_strcmp(state, "sub"))
		return (0x05);
	else if (!ft_strcmp(state, "and"))
		return (0x06);
	else if (!ft_strcmp(state, "or"))
		return (0x07);
	else if (!ft_strcmp(state, "xor"))
		return (0x08);
	else if (!ft_strcmp(state, "zjmp"))
		return (0x09);
	else if (!ft_strcmp(state, "ldi"))
		return (0x0a);
	else if (!ft_strcmp(state, "sti"))
		return (0x0b);
	else if (!ft_strcmp(state, "fork"))
		return (0x0c);
	else if (!ft_strcmp(state, "lld"))
		return (0x0d);
	else if (!ft_strcmp(state, "lldi"))
		return (0x0e);
	else if (!ft_strcmp(state, "lfork"))
		return (0x0f);
	else if (!ft_strcmp(state, "aff"))
		return (0x10);
}

void	init_arg_code(char *str)
{
	int index;
	
	index = 0;
	while (index < 8)
	{
		str[index++] = '0';
	}
}

void	calculate_arg_code(char *str, int index, char *dest)
{
	index = ignore_spaces(str, index);
	if (str[index] == 'r')
		dest[1] = '1';
	else if (str[index] == DIRECT_CHAR)
		dest[0] = '1';
	else
	{
		dest[0] = '1';
		dest[1] = '1';
	}
	while (str[index] != MTY_SPACE_1 && str[index] != MTY_SPACE_2 && str[index] != '\0')
	{
		index++;
	}
	index = ignore_spaces(str, index);
	if (str[index] == 'r')
		dest[3] = '1';
	else if (str[index] == DIRECT_CHAR)
		dest[2] = '1';
	else
	{
		dest[2] = '1';
		dest[3] = '1';
	}
	while (str[index] != MTY_SPACE_1 && str[index] != MTY_SPACE_2 && str[index] != '\0')
	{
		index++;
	}
	index = ignore_spaces(str, index);
	if (str[index] == 'r')
		dest[5] = '1';
	else if (str[index] == DIRECT_CHAR)
		dest[4] = '1';
	else
	{
		dest[4] = '1';
		dest[5] = '1';
	}
}

t_command	*generate_command(char *str, char **labels)
{
	t_command	*inst;
	int			index;
	int			i;

	inst = malloc(sizeof(t_command));
	index = 0;
	while (str[index] != MTY_SPACE_1 && str[index] != MTY_SPACE_2)
		index++;
	index = ignore_spaces(str, index);
	inst->name = get_inst_code(str, &index);
	i = 0;
	init_arg_code(inst->arg_code);
	calculate_arg_code(str, index, inst->arg_code);
	while (i < 3)
	{
		if (str[index] == SEPARATOR_CHAR)
			index++;
		index = ignore_spaces(str, index);
		
	}
}

t_champion *generate_champ(t_parser *data)
{
	t_champion *hero;
	int	index;
	int	i;

	hero = (t_champion *)malloc(sizeof(t_champion));
	hero->name = get_champ_name_comm(data->file[0].line);
	hero->comment = get_champ_name_comm(data->file[1].line);
	hero->commands = (t_command **)malloc(sizeof(t_command *) * (data->file_size - 2));
	index = 2;
	i = 0;
	while (index < data->file_size)
	{
		hero->commands[i] = generate_command(data->file[index].line, data->label);
		index++;
		i++;
	}
	return (hero);
}*/