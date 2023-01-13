/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:23:15 by marius            #+#    #+#             */
/*   Updated: 2023/01/13 10:30:00 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"


//a simple function that exits the program in case of bad call (wrong filename, no file)
void	exit_usage(void)
{
	ft_printf("Usage : ./assembler [filename.s]");
	exit(1);
}


//a function to check the file name and exit the program in case it does not end with .s
bool checkname(char *str)
{
	int index;

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

// The assembler is meant to read through the .s file representing a champion
// and take the code written in assembly language and turn it in bytecode
// that the Virtual Machine can read. 
int	main (int argc, char **argv)
{
	int fd;
	t_data *data;
	
	if (argc != 2)
		exit_usage();
	if (!checkname(argv[1]))
		exit_usage();
	fd = open(argv[1],O_RDONLY);
	data = (t_data *)malloc(sizeof(t_data));
	if (!scan_file(data, fd))
		exit_usage();
	return (0);
}