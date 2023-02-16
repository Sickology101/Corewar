/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:23:15 by marius            #+#    #+#             */
/*   Updated: 2023/02/16 16:31:33 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/assembler.h"

void	exit_usage(int flag)
{
	if (flag == 1)
		ft_printf("Invalid text in assembly code\n");
	else if (flag == 2)
		ft_printf("Invalid label char\n");
	else if (flag == 3)
		ft_printf("Invalid statement\n");
	else if (flag == 4)
		ft_printf("Incomplete assembly code\n");
	else if (flag == 5)
		ft_printf("No name or comment in file\n");
	else if (flag == 6)
		ft_printf("File converted succesfuly\n");
	else if (flag == 7)
		ft_printf("Label not found\n");
	else if (flag == 8)
		ft_printf("No newline at the end\n");
	else
		ft_printf("Usage : ./assembler [filename.s]\n");
	exit(1);
}

bool	check_newline(char *filename)
{
	int		fd;
	char	cache[4];
	char	*tail;

	fd = open(filename, O_RDONLY);
	lseek(fd, -3, SEEK_END);
	read(fd, cache, 3);
	cache[3] = '\0';
	tail = ft_strrchr(cache, '\n');
	if (tail == NULL)
		return (false);
	while (*tail)
	{
		if (ft_isprint(*tail++))
			return (false);
	}
	return (true);
}

/*
a function to check the file name and exit the program in case 
it does not end with .s 
*/
bool	checkname(char *str)
{
	int	index;

	index = ft_strlen(str);
	index--;
	if (str[index--] == 's')
	{
		if (str[index] == '.')
		{
			return (true);
		}
	}
	return (false);
}

/* The assembler is meant to read through the .s file representing a champion
 and take the code written in assembly language and turn it in bytecode
 that the Virtual Machine can read. 
	TODO  add error if file inexistent; 
*/
int	main(int argc, char **argv)
{
	t_parser	*data;

	if (argc != 2)
		exit_usage(0);
	if (!checkname(argv[1]))
		exit_usage(0);
	if (!check_newline(argv[1]))
		exit_usage(8);
	data = (t_parser *)malloc(sizeof(t_parser));
	data->fd = open(argv[1], O_RDONLY);
	data->found[0] = 0;
	data->found[1] = 0;
	scan_file(data);
	populate_t_dir(data);
	write_to_file(data, argv);
	exit_usage(6);
	return (0);
}
