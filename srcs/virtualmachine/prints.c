/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:41:35 by macbook           #+#    #+#             */
/*   Updated: 2023/01/17 15:51:07 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	print_champion_path_and_id(t_data *const data)
{
	t_player	*tmp;

	printf("----------\n");
	printf("\nLIST OF CHAMPS WITH THEIR ID'S\n");
	tmp = data->player;
	while (tmp)
	{
		printf("%s ", tmp->path);
		printf("id = %d\n", tmp->id);
		tmp = tmp->next;
	}
}

void	print_introduction(t_data *const data)
{
	t_player	*tmp;

	tmp = data->player;
	ft_printf("\n\n");
	ft_printf("Introducing contestants...\n");
	while (tmp)
	{
		printf("* Player %d, weighing %zu bytes, \"%s\" (\"%s\") !\n",
			tmp->id, tmp->exec_size, tmp->name, tmp->comment);
		tmp = tmp->next;
	}
}

void	print_arena(t_data *const data)
{
	int	i;
	int fd;

	i = 0;

	fd = open("mycore.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
		{
			if (i != 0)
				dprintf(fd, "\n");
			if (i == 0)
				dprintf(fd, "0x");
			dprintf(fd, "%#.4x : ", i);
		}
		dprintf(fd, "%.2x ", data->arena[i]);
		i++;
	}
	dprintf(fd, "\n");
}

/*
You can install Hex Editor and open .cor file there
And use this function to print player code
It will print it in the same format as hex editor, so
it's easy to read and compare them
*/
void	print_player_code(t_player *player)
{
	int	i;

	i = 0;
	while (i < (int)player->exec_size)
	{
		if (i % 16 == 0)
			ft_printf("\n");
		ft_printf("%.2x ", player->exec_code[i]);
		i++;
	}
	ft_printf("\nbytes = %d\n\n", i);
}
