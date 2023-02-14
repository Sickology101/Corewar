/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:23:15 by marius            #+#    #+#             */
/*   Updated: 2023/02/14 16:35:39 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

// void	print_file(t_parser *data)
// {
// 	int	index;
// 	int	i;

// 	ft_printf("%s\n%s\n", data->name, data->comment);
// 	index = 2;
// 	while (index < data->file_size)
// 	{
// 		if (data->line[index]->type == 0)
// 			ft_printf("%s", data->line[index]->label);
// 		else if (data->line[index]->type == 1)
// 		{
// 			ft_printf("%d ", data->line[index]->state_code);
// 			if (data->line[index]->arg_code_req == true)
// 			{
// 				i = 0;
// 				while (i < 8)
// 				{
// 					ft_printf("%d", data->line[index]->arg_code[i]);
// 					i++;
// 				}
// 			}
// 			i = 0;
// 			while (i < data->line[index]->req_arg_num)
// 			{
// 				ft_printf(" [%d]%d", data->line[index]->arg_type[i], data->line[index]->arg_num[i]);
// 				i++;
// 			}
// 		}
// 		else
// 		{
// 			ft_printf("%s ", data->line[index]->label);
// 			ft_printf("%d ", data->line[index]->state_code);
// 			if (data->line[index]->arg_code_req == true)
// 			{
// 				i = 0;
// 				while (i < 8)
// 				{
// 					ft_printf("%d", data->line[index]->arg_code[i]);
// 					i++;
// 				}
// 			}
// 			i = 0;
// 			while (i < data->line[index]->req_arg_num)
// 			{
// 				ft_printf(" [%d]%lld", data->line[index]->arg_type[i], data->line[index]->arg_num[i]);
// 				i++;
// 			}
// 		}
// 		ft_printf("   size = %d", data->line[index]->size);
// 		ft_printf("      dir_size =  %d\n", data->line[index]->dir_size);
// 		index++;
// 	}
// }

/*
a simple function that exits the program in case of 
bad call (wrong filename, no file) 
*/
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
	char	cache[1];
	int		ret;
	
	fd = open(filename, O_RDONLY); 
	ret = read(fd, cache, 1);
	while (ret)
		ret = read(fd, cache, 1);
	return (cache[0] == '\n');
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

void	our_free(t_parser *data)
{
	int index;
	int	i;

	index = 2;
	while (index < data->file_size)
	{
		i = 0;
		if (data->line[index]->label != NULL)
			free(data->line[index]->label);
		if (data->line[index]->type != 0)
		{
			if (data->line[index]->arg_num != NULL)
				free(data->line[index]->arg_num);
			if (data->line[index]->statement != NULL)
				free(data->line[index]->statement);
			if (index > 1)
			{
				while (i < data->line[index]->req_arg_num)
					free(data->line[index]->arg[i++]);
			}
		}
		if (data->line[index]->str != NULL)
			free(data->line[index]->str);
		if (data->line[index] != NULL)
			free(data->line[index]);
		index++;
	}
	free(data->line[0]->str);
	free(data->line[1]->str);
	if (data->line != NULL)
		free(data->line);
	free(data);
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
	scan_file(data);
	populate_t_dir(data);
	write_to_file(data, argv);
	//our_free(data);
	exit_usage(6);
	return (0);
}
