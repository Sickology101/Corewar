/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:02:13 by parkharo          #+#    #+#             */
/*   Updated: 2023/01/14 14:07:46 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "assembler.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

char	**get_champ_name(void)
{
	t_data	*data;

	data = get_data();
	return (&data->file[0]);	
}

char **get_comment(void)
{
	t_data	*data;

	data = get_data();
	return (&data->file[1]);	
}




void	populate_data(void)
{
	char	*line;
	int ret = ft_getnextline(fd, 1818238, &line);

	get_data()->name = line;
}

void	update_champ(t_champion *champ)
{
	champ->name = ft_strdup(get_champ_name());
}