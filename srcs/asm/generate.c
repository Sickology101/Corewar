/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:15:45 by marius            #+#    #+#             */
/*   Updated: 2023/01/19 11:44:12 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

static	int	get_size(char *str, int index)
{
	int size;

	size = 0;
	while (str[index] != '"')
	{
		size++;
		index++;
	}
	return (size);
}

static char *get_champ_name_comm(char *str)
{
	char *dest;
	int	index;
	int	i;
	int	size;

	index = 0;
	while (str[index] != '"')
	{
		index++;
	}
	index++;
	i = 0;
	size = get_size(str, index);
	dest = (char *)malloc(sizeof(char) * size);
	dest[size] = '\0';
	while (str[index] != '"')
	{
		dest[i] = str[index];
		i++;
		index++;
	}
	return (dest);
}

t_champion *generate_champ(t_parser *data)
{
	t_champion *hero;

	hero = (t_champion *)malloc(sizeof(t_champion));
	hero->name = get_champ_name_comm(data->file[0]);
	hero->comment = get_champ_name_comm(data->file[1]);
	return (hero);
}