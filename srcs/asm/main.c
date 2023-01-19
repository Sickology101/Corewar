/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:23:15 by marius            #+#    #+#             */
/*   Updated: 2023/01/19 11:44:32 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"


//a simple function that exits the program in case of bad call (wrong filename, no file)
void	exit_usage(int	flag)
{
	if (flag == 1)
		ft_printf("Invalid text in assembly code\n");
	else if (flag == 2)
		ft_printf("Invalid label char\n");
	else if (flag == 3)
		ft_printf("Invalid statement\n");
	else
		ft_printf("Usage : ./assembler [filename.s]\n");
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
	t_parser 		*data;
	t_champion	*hero;
	
	if (argc != 2)
		exit_usage(0);
	if (!checkname(argv[1]))
		exit_usage(0);
	fd = open(argv[1],O_RDONLY);
	data = (t_parser *)malloc(sizeof(t_parser));
	data->label_num = 0;
	if (!scan_file(data, fd))
		exit_usage(0);
	hero = generate_champ(data);
	ft_printf("%s\n%s\n",hero->name, hero->comment);
	//write_bytecode(hero, argv);
	return (0);
}