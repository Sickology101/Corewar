/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:58:29 by parkharo          #+#    #+#             */
/*   Updated: 2023/02/02 11:51:48 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "assembler.h"

static int	size_code(t_parser *a)
{
	int ret;
	int	i;

	ret = 0;
	i = 2;
	while (i <= a->file_size)
		ret += a->line[i++]->size;
	return (ret);
}

static void		write_name_comment(int fd, t_parser *a)
{
	int		i;

	i = 0;
	write_bytes(fd, COREWAR_EXEC_MAGIC, 4);
	while (a->name[++i])
		write_bytes(fd, a->name[i], 1);
	while (++i < PROG_NAME_LENGTH + NULL_SEPARATOR)
		write_bytes(fd, 0, 1);
	write_bytes(fd, size_code(a), 4);
	i = 0;
	while (a->comment[++i])
		write_bytes(fd, a->comment[i], 1);
	while (++i < COMMENT_LENGTH + NULL_SEPARATOR)
		write_bytes(fd, 0, 1);
}



static void		writer(t_parser *a, char *line)
{
	char	*file_name;
	int		fd;
	int		filename_len;

	filename_len = ft_strlen(line) - 1;
	while (line[filename_len] && line[filename_len] != '.')
		filename_len--;
	if (filename_len == -1)
		file_name = ft_strdup(".cor");
	else
		file_name = ft_strndup(line, filename_len);
	file_name = join_free(file_name, ".cor", 0);
	file_name[ft_strlen(file_name) - 1] = 0;
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	write_name_comment(fd, a);
	//writing_command(fd, a);
	ft_printf("Writing output program to %s\n", file_name);
	close(fd);
	ft_strdel(&file_name);
}

void			write_to_file(t_parser *a, char **av)
{
	writer(a, av[1]);
}
