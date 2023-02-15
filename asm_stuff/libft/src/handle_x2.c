/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:23:28 by marius            #+#    #+#             */
/*   Updated: 2022/04/05 15:16:30 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	g_pre;
static int	g_zero;
static int	g_n;

static void	minflag2(unsigned long long x, int len, char *num, t_print *tab)
{
	if (!(tab->prec == 0 && x == 0))
		add_str_to_buff(num, tab);
	else
		add_to_buff(' ', tab);
	g_n = tab->width - (g_pre + g_zero + len);
	while (g_n > 0)
	{
		add_to_buff(' ', tab);
		g_n--;
	}
	free (num);
}

void	x_minflag(unsigned long long x, int len, char *num, t_print *tab)
{
	if (tab->flags[4] == '#' && x != 0)
	{
		if (tab->var)
			add_str_to_buff("0X", tab);
		else
			add_str_to_buff("0x", tab);
		g_pre = 2;
	}
	else
		g_pre = 0;
	g_zero = tab->prec - len;
	if (g_zero > 0)
	{
		g_n = g_zero;
		while (g_n > 0)
		{
			add_to_buff('0', tab);
			g_n--;
		}
	}
	else
		g_zero = 0;
	minflag2(x, len, num, tab);
}

void	x_zeroflag(unsigned long long x, int len, char *num, t_print *tab)
{
	if (tab->flags[4] == '#' && x != 0)
	{
		if (tab->var)
			add_str_to_buff("0X", tab);
		else
			add_str_to_buff("0x", tab);
		g_pre = 2;
	}
	else
		g_pre = 0;
	g_zero = tab->width - (g_pre + len);
	while (g_zero > 0)
	{
		add_to_buff('0', tab);
		g_zero--;
	}
	add_str_to_buff(num, tab);
	free(num);
}

static void	noflag2(unsigned long long x, char *num, t_print *tab)
{
	if (g_pre && x == 0)
		add_str_to_buff("  ", tab);
	else if (g_pre)
	{
		if (tab->var)
			add_str_to_buff("0X", tab);
		else
			add_str_to_buff("0x", tab);
	}
	while (g_zero > 0)
	{
		add_to_buff('0', tab);
		g_zero--;
	}
	if (!(tab->prec == 0 && x == 0))
		add_str_to_buff(num, tab);
	else
		add_to_buff(' ', tab);
	free(num);
}

void	x_noflag(unsigned long long x, int len, char *num, t_print *tab)
{
	if (tab->flags[4] == '#' && x != 0)
		g_pre = 2;
	else
		g_pre = 0;
	if (tab->prec > len)
		g_zero = tab->prec - len;
	else
		g_zero = 0;
	g_n = tab->width - (g_pre + g_zero + len);
	while (g_n > 0)
	{
		add_to_buff(' ', tab);
		g_n--;
	}
	noflag2(x, num, tab);
}
