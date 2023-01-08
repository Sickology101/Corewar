/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_o.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:20:48 by marius            #+#    #+#             */
/*   Updated: 2022/04/05 15:21:15 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long long	g_o;
static char					*g_num;
static int					g_len;
static int					g_zero;
static int					g_n;

static void	minflag2(t_print *tab)
{
	if (!(tab->prec == 0 && g_o == 0))
		add_str_to_buff(g_num, tab);
	else
		add_to_buff(' ', tab);
	g_n = tab->width - (g_zero + g_len);
	while (g_n > 0)
	{
		add_to_buff(' ', tab);
		g_n--;
	}
}

static void	minflag(t_print *tab)
{
	g_zero = tab->prec - g_len;
	if (g_zero > 0)
	{
		g_n = g_zero;
		while (g_n > 0)
		{
			add_to_buff('0', tab);
			g_n--;
		}
	}
	else if (tab->flags[4] == '#' && g_o)
	{
		add_to_buff('0', tab);
		g_zero = 1;
	}
	else
		g_zero = 0;
	minflag2(tab);
}

static void	zeroflag(t_print *tab)
{
	g_zero = tab->width - g_len;
	if (g_zero > 0)
	{
		while (g_zero > 0)
		{
			add_to_buff('0', tab);
			g_zero--;
		}
	}
	else if (tab->flags[4] == '#' && g_o)
	{
		add_to_buff('0', tab);
	}
	add_str_to_buff(g_num, tab);
}

static void	noflag(t_print *tab)
{
	if (tab->prec > g_len)
		g_zero = tab->prec - g_len;
	else if (tab->flags[4] == '#' && g_o)
		g_zero = 1;
	else
		g_zero = 0;
	g_n = tab->width - (g_zero + g_len);
	while (g_n-- > 0)
		add_to_buff(' ', tab);
	while (g_zero-- > 0)
		add_to_buff('0', tab);
	if (!(tab->prec == 0 && g_o == 0))
		add_str_to_buff(g_num, tab);
	else
		add_to_buff(' ', tab);
}

void	handle_o(t_print *tab)
{
	ulong_init(&g_o, tab);
	if (!g_o && !tab->prec && !tab->width)
	{
		if (tab->flags[4] == '#')
			add_to_buff('0', tab);
		return ;
	}
	in_octave(&g_num, g_o);
	g_len = ft_strlen(g_num);
	if (tab->flags[3] == '-')
		minflag(tab);
	else if (tab->flags[0] == '0' && tab->prec == -1)
		zeroflag(tab);
	else
		noflag(tab);
	free(g_num);
}
