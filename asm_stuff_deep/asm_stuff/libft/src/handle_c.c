/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:36:25 by marius            #+#    #+#             */
/*   Updated: 2022/04/11 10:48:01 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	actions(char c, t_print *tab)
{
	size_t	index;

	if (tab->flags[3] == '-')
	{
		add_to_buff(c, tab);
		index = 1;
		while (index++ < tab->width)
		{
			add_to_buff(' ', tab);
		}
		tab->printed--;
	}
	else
	{
		index = 0;
		while (index++ < tab->width - 1)
		{
			add_to_buff(' ', tab);
		}
		add_to_buff(c, tab);
		tab->printed--;
	}
}

void	handle_c(t_print *tab)
{
	char	c;

	c = (char)va_arg(tab->args, int);
	if (tab->width > 1)
		actions(c, tab);
	else
		add_to_buff(c, tab);
}
