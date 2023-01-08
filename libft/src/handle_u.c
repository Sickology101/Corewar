/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:57:45 by marius            #+#    #+#             */
/*   Updated: 2022/04/05 16:01:24 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long long	g_u;
static char					*g_num;
static int					g_len;
static int					g_zero;
static int					g_n;

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
	else
		g_zero = 0;
	if (!(tab->prec == 0 && g_u == 0))
		add_str_to_buff(g_num, tab);
	g_n = tab->width - (g_zero + g_len);
	while (g_n > 0)
	{
		add_to_buff(' ', tab);
		g_n--;
	}
}

static void	zeroflag(t_print *tab)
{
	g_zero = tab->width - g_len;
	while (g_zero > 0)
	{
		add_to_buff('0', tab);
		g_zero--;
	}
	add_str_to_buff(g_num, tab);
}

static void	noflag(t_print *tab)
{
	if (tab->prec > g_len)
		g_zero = tab->prec - g_len;
	else
		g_zero = 0;
	g_n = tab->width - (g_zero + g_len);
	while (g_n > 0)
	{
		add_to_buff(' ', tab);
		g_n--;
	}
	while (g_zero > 0)
	{
		add_to_buff('0', tab);
		g_zero--;
	}
	if (!(tab->prec == 0 && g_u == 0))
		add_str_to_buff(g_num, tab);
}

void	handle_u(t_print *tab)
{
	ulong_init(&g_u, tab);
	g_num = abs_itoa_long(g_u);
	g_len = ft_strlen(g_num);
	if (tab->flags[3] == '-')
		minflag(tab);
	else if (tab->flags[0] == '0' && tab->prec == -1)
		zeroflag(tab);
	else
		noflag(tab);
	free(g_num);
}
