/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:48:00 by marius            #+#    #+#             */
/*   Updated: 2022/05/29 16:41:48 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	minflag(char *str, t_print *tab)
{
	int	index;
	int	a;

	index = 0;
	if (tab->prec == 0)
		return ;
	else if (tab->prec > 0)
	{
		a = ft_strnlen(str, tab->prec);
		while (index < tab->prec && str[index] != '\0')
			add_to_buff(str[index++], tab);
	}
	else
	{
		a = ft_strlen(str);
		add_str_to_buff(str, tab);
	}
	index = tab->width - a;
	while (index > 0)
	{
		add_to_buff(' ', tab);
		index--;
	}
}

static void	noflag(char *s, t_print *tab)
{
	int	index;
	int	a;

	if (tab->prec >= 0)
			a = ft_strnlen(s, tab->prec);
	else
		a = ft_strlen(s);
	index = tab->width - a;
	while (index > 0)
	{
		add_to_buff(' ', tab);
		index--;
	}
	index = 0;
	while (index != a)
	{
		add_to_buff(s[index++], tab);
	}
}

void	handle_s(t_print *tab)
{
	char	*s;

	s = va_arg(tab->args, char *);
	if (!s)
	{
		add_str_to_buff("(null)", tab);
		return ;
	}
	if (tab->flags[3] == '-')
		minflag(s, tab);
	else
		noflag(s, tab);
}
