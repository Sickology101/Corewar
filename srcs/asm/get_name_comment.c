/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_comment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:28:58 by marius            #+#    #+#             */
/*   Updated: 2023/02/15 21:30:59 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/assembler.h"

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
		{
			free(line);
			return ;
		}
		exit_usage(1);
	}
	data->line[flag]->str = ft_strupdate(data->line[flag]->str, "\n");
	free(line);
	ret = get_next_line(data->fd, &line);
	if (ret == 0)
		exit_usage(4);
	save_name_comment(data, line, flag);
}

void	process_name_comment(t_parser *data, char *line, int i)
{
	data->line[i] = (t_line *)malloc(sizeof(t_line));
	data->line[i]->str = ft_strnew(0);
	data->found[i] = 1;
	save_name_comment(data, line, i);
}

void	get_name_comment(t_parser *data)
{
	int		ret;
	char	*line;
	int		i;

	ret = get_next_line(data->fd, &line);
	if (ret == 0)
		exit_usage(4);
	while (ignore_comment_empty(line))
	{
		free(line);
		ret = get_next_line(data->fd, &line);
		if (ret == 0)
			exit_usage(4);
	}
	i = ft_strnccmp(line);
	if (i == 1 && data->found[0] == 0)
		process_name_comment(data, line, 0);
	else if (i == 2 && data->found[1] == 0)
		process_name_comment(data, line, 1);
	else
		exit_usage(5);
	if (data->line[1] == NULL || data->line[0] == NULL)
		get_name_comment(data);
}
