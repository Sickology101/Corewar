/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:14:17 by marius            #+#    #+#             */
/*   Updated: 2022/04/11 12:27:11 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long double	g_f;
static char			*g_str;
static int			g_pre;
static int			g_len;
static int			g_index;

static void	minflag(t_print *tab)
{
	if (tab->flags[2] == '+' && g_str[0] != '-')
	{
		add_to_buff('+', tab);
		g_pre = 1;
	}
	else if (tab->flags[1] == ' ' && g_str[0] != '-')
	{
		add_to_buff(' ', tab);
		g_pre = 1;
	}
	else
		g_pre = 0;
	add_str_to_buff(g_str, tab);
	g_index = tab->width - (g_len + g_pre);
	while (g_index > 0)
	{
		add_to_buff(' ', tab);
		g_index--;
	}
}

static void	zeroflag(t_print *tab)
{
	if (tab->flags[2] == '+' && g_str[0] != '-')
	{
		add_to_buff('+', tab);
		g_pre = 1;
	}
	else if (tab->flags[1] == ' ' && g_str[0] != '-')
	{
		add_to_buff(' ', tab);
		g_pre = 1;
	}
	else
		g_pre = 0;
	g_index = tab->width - (g_len + g_pre);
	while (g_index > 0)
	{
		add_to_buff('0', tab);
		g_index--;
	}
	add_str_to_buff(g_str, tab);
}

static void	noflag(t_print *tab)
{
	if (tab->flags[1] == ' ' && g_str[0] != '-')
		g_pre = 1;
	else if (tab->flags[2] == '+' && g_str[0] != '-')
		g_pre = 1;
	else
		g_pre = 0;
	g_index = tab->width - (g_len + g_pre);
	while (g_index > 0)
	{
		add_to_buff(' ', tab);
		g_index--;
	}
	if (tab->flags[2] == '+' && g_str[0] != '-')
		add_to_buff('+', tab);
	else if (tab->flags[1] == ' ' && g_str[0] != '-')
		add_to_buff(' ', tab);
	add_str_to_buff(g_str, tab);
}

static int	check_special(t_print *tab)
{
	if (is_inf(g_f) == 1)
	{
		add_str_to_buff("inf", tab);
		return (1);
	}
	else if (is_inf(g_f) == -1)
	{
		add_str_to_buff("-inf", tab);
		return (1);
	}
	else if (is_nan(g_f) == 1)
	{
		add_str_to_buff("nan", tab);
		return (1);
	}
	return (0);
}

void	handle_f(t_print *tab)
{
	if (tab->length[0] == 'L')
		g_f = va_arg(tab->args, long double);
	else
		g_f = va_arg(tab->args, double);
	if (check_special(tab) == 1)
		return ;
	in_double(&g_str, g_f, tab);
	g_len = ft_strlen(g_str);
	if (tab->flags[3] == '-')
		minflag(tab);
	else if (tab->flags[0] == '0')
		zeroflag(tab);
	else
		noflag(tab);
	free(g_str);
}
