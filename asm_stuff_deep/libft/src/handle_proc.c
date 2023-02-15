/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:44:02 by marius            #+#    #+#             */
/*   Updated: 2022/04/05 15:59:09 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	noflag(t_print *tab)
{
	int	index;

	index = tab->width - 1;
	while (index > 0)
	{
		if (tab->flags[0] == '0')
			add_to_buff('0', tab);
		else
			add_to_buff(' ', tab);
		index--;
	}
	add_to_buff('%', tab);
}

void	handle_proc(t_print *tab)
{
	int	index;

	if (tab->flags[3] == '-')
	{
		add_to_buff('%', tab);
		index = tab->width - 1;
		while (index > 0)
		{
			add_to_buff(' ', tab);
			index--;
		}
	}
	else
		noflag(tab);
}
