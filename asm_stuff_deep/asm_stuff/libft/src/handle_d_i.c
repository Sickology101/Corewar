/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_d_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:42:21 by marius            #+#    #+#             */
/*   Updated: 2022/04/05 15:41:44 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long	g_num;
static char			*g_str;
static int			g_pre;
static int			g_len;
static int			g_zero;
static int			g_index;

int	add_sign(t_print *tab)
{
	if (tab->flags[2] == '+' && g_num >= 0)
	{
		add_to_buff('+', tab);
		return (1);
	}
	else if (tab->flags[1] == ' ' && g_num >= 0)
	{
		add_to_buff(' ', tab);
		return (1);
	}
	else if (g_num < 0)
	{
		add_to_buff('-', tab);
		return (1);
	}
	return (0);
}

static void	read_arg(t_print *tab)
{
	if (!(ft_strcmp(tab->length, "l")))
		g_num = va_arg(tab->args, long);
	else if (!(ft_strcmp(tab->length, "ll")))
		g_num = va_arg(tab->args, long long);
	else if (!(ft_strcmp(tab->length, "h")))
		g_num = (short)va_arg(tab->args, int);
	else if (!(ft_strcmp(tab->length, "hh")))
		g_num = (char)va_arg(tab->args, int);
	else
		g_num = va_arg(tab->args, int);
	if (g_num < 0)
		g_str = abs_itoa_long(-g_num);
	else
		g_str = abs_itoa_long(g_num);
	g_len = ft_strlen(g_str);
}

static void	minflag(t_print *tab)
{
	g_pre = add_sign(tab);
	g_zero = tab->prec - g_len;
	g_index = g_zero;
	if (g_zero < 0)
		g_zero = 0;
	while (g_index > 0)
	{
		add_to_buff('0', tab);
		g_index--;
	}
	if (!(tab->prec == 0 && g_num == 0))
		add_str_to_buff(g_str, tab);
	else
		add_to_buff(' ', tab);
	g_index = tab->width - (g_pre + g_zero + g_len);
	while (g_index > 0)
	{
		add_to_buff(' ', tab);
		g_index--;
	}
}

static void	noflag(t_print *tab)
{
	g_index = tab->width - (g_zero + g_len);
	while (g_index > 1)
	{
		add_to_buff(' ', tab);
		g_index--;
	}
	if (!add_sign(tab) && g_index == 1)
	{
		add_to_buff(' ', tab);
	}
	while (g_zero > 0)
	{
		add_to_buff('0', tab);
		g_zero--;
	}
	if (!(tab->prec == 0 && g_num == 0))
		add_str_to_buff(g_str, tab);
	else if (tab->prec == 0 && g_num == 0 && tab->width > 0)
	{
		add_to_buff(' ', tab);
	}
}

void	handle_d_i(t_print *tab)
{
	read_arg(tab);
	if (tab->flags[3] == '-')
		minflag(tab);
	else if (tab->flags[0] == '0' && tab->prec == -1)
	{
		g_index = tab->width - (add_sign(tab) + g_len);
		while (g_index > 0)
		{
			add_to_buff('0', tab);
			g_index--;
		}
		add_str_to_buff(g_str, tab);
	}
	else
	{
		g_zero = tab->prec - g_len;
		if (g_zero < 0)
			g_zero = 0;
		noflag(tab);
	}
	free(g_str);
}
