/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:41:35 by macbook           #+#    #+#             */
/*   Updated: 2023/01/12 20:41:36 by macbook          ###   ########.fr       */
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
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			tmp->id, tmp->exec_size, tmp->name, tmp->comment);
		tmp = tmp->next;
	}
}

void	print_arena(t_data *const data)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("\n");
		ft_printf("%.2x ", data->arena[i]);
		i++;
	}
}
