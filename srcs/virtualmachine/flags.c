/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:58:50 by igaplich          #+#    #+#             */
/*   Updated: 2023/01/15 18:58:51 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	validate_and_receive_dump_flag_arg(int *i, const char **av, int ac,
								t_data *const data)
{
	size_t	j;

	if ((*i + 1) >= ac)
		exit_error_message("Too few arguments after flag!");
	*i = *i + 1;
	j = 0;
	while (av[*i][j])
	{
		if (!ft_isdigit(av[*i][j]))
			exit_error_message("Wrong argument after -dump flag!");
		j++;
	}
	if (data->dump_cycles == -1)
		data->dump_cycles = ft_atoi(av[*i]);
	else
		exit_error_message("-dump set multiple times!");
	*i = *i + 1;
}

int	validate_and_receive_n_flag(int *i, const char **av, int ac)
{
	if (*av[*i] == '-')
	{
		if (!ft_strcmp(av[*i], "-n"))
		{
			if ((*i + 2) >= ac)
				exit_error_message("Too few arguments after -n flag!");
			*i = *i + 1;
			if (av[*i][0] < '1' || av[*i][0] > '4' || av[*i][1])
				exit_error_message("Wrong argument after -n flag!");
			*i = *i + 1;
			return (av[*i - 1][0] - '0');
		}
		else
			exit_error_message("Unsupported flag!");
	}
	return (0);
}

void	check_n_flag_unique_ids(t_data *const data)
{
	char		ids[4];
	t_player	*tmp;
	int			i;

	i = -1;
	while (++i < data->player_amount)
		ids[i] = 0;
	tmp = data->player;
	while (tmp)
	{
		if (tmp->id != 0 && ids[tmp->id - 1] == 0)
			ids[tmp->id - 1] = 1;
		else if (tmp->id != 0 && ids[tmp->id - 1] != 0)
			exit_error_message("-n number is used multiple times!");
		tmp = tmp->next;
	}
}
