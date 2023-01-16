/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:02:13 by parkharo          #+#    #+#             */
/*   Updated: 2023/01/14 17:05:06 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "assembler.h"

t_data	*get_data(void)
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
