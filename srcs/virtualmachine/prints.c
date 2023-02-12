/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:41:35 by macbook           #+#    #+#             */
/*   Updated: 2023/02/09 19:00:16 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	print_introduction(t_data *const data)
{
	t_player	*tmp;

	tmp = NULL;
	if (data->player)
		tmp = data->player;
	else 
		ft_printf("Not enough players!");
	ft_printf("Introducing contestants...\n");
	while (tmp)
	{
		ft_printf("* Player %d, weighing %d bytes, ", tmp->id, tmp->exec_size);
		ft_putchar('"');
		if (tmp->name == NULL)
			tmp->name = ft_strdup("");
		ft_printf("%s", tmp->name);
		ft_putchar('"');
		ft_putchar(' ');
		ft_putchar('(');
		ft_putchar('"');
		ft_printf("%s", tmp->comment);
		ft_putchar('"');
		ft_printf(") !\n");
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
		{
			if (i != 0)
				ft_printf("\n");
			if (i == 0)
				ft_printf("0x");
			ft_printf("%#.4x : ", i);
		}
		ft_printf("%.2x ", data->arena[i]);
		i++;
	}
	ft_printf("\n");
}

void	print_arena_term(t_data *const data)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
		{
			if (i != 0)
				ft_printf("\n");
			if (i == 0)
				ft_printf("0x");
			ft_printf("%#.4x : ", i);
		}
		ft_printf("%.2x ", data->arena[i]);
		i++;
	}
	ft_printf("\n");
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
