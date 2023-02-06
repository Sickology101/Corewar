/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_comment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:28:58 by marius            #+#    #+#             */
/*   Updated: 2023/02/06 10:44:02 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int	check_quotes(char *line)
{
	int	index;
	int	flag;

	flag = 0;
	index = 0;
	while (line[index] != '\0')
	{
		if (line[index] == '"')
			flag++;
		index++;
	}
	return (flag);
}

bool	check_valid_syntax(char *str)
{
	int	index;
	int	flag;

	index = 0;
	flag = 0;
	while (flag != 2)
	{
		if (str[index] == '"')
			flag++;
		index++;
	}
	index = ignore_spaces(str, index);
	if (str[index] == '\0' || str[index] == '#')
		return (true);
	return (false);
}

void	save_name_comment(t_parser *data, char *line, int flag)
{
	int	ret;

	data->line[flag]->str = ft_strupdate(data->line[flag]->str, line);
	if (check_quotes(data->line[flag]->str) == 0)
		exit_usage(1);
	else if (check_quotes(data->line[flag]->str) > 2)
		exit_usage(1);
	else if (check_quotes(data->line[flag]->str) == 2)
	{
		if (check_valid_syntax(data->line[flag]->str))
			return ;
		else
			exit_usage(1);
	}
	else
	{
		data->line[flag]->str = ft_strupdate(data->line[flag]->str, "\n");
		ret = get_next_line(data->fd, &line);
		if (ret == 0)
			exit_usage(4);
		save_name_comment(data, line, flag);
	}
}

void	process_name_comment(t_parser *data, char *line, int i)
{
	data->line[i] = (t_line *)malloc(sizeof(t_line));
	data->line[i]->str = ft_strnew(0);
	save_name_comment(data, line, i);
}

void	get_name_comment(t_parser *data)
{
	int		ret;
	char	*line;

	ret = get_next_line(data->fd, &line);
	if (ret == 0)
		exit_usage(4);
	while (ignore_comment_empty(line))
	{
		ret = get_next_line(data->fd, &line);
		if (ret == 0)
			exit_usage(4);
	}
	if (!ft_strncmp(line, ".name", 5))
		process_name_comment(data, line, 0);
	else if (!ft_strncmp(line, ".comment", 8))
		process_name_comment(data, line, 1);
	else
		exit_usage(5);
	if (data->line[1] == NULL || data->line[0] == NULL)
		get_name_comment(data);
}
