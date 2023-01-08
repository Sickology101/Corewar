/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:13:52 by marius            #+#    #+#             */
/*   Updated: 2022/04/05 15:56:55 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*g_num;
static int	g_len;

static int	count_hex(unsigned long long x)
{
	int	index;

	index = 1;
	while (x / 16)
	{
		x /= 16;
		index++;
	}
	return (index);
}

static void	in_hex(unsigned long long x, int var)
{
	char	reg;
	int		index;

	g_num = (char *)malloc(sizeof(char) * (g_len + 1));
	g_num[g_len] = '\0';
	if (!var)
		reg = 'a';
	else
		reg = 'A';
	index = g_len - 1;
	while (x / 16)
	{
		if ((x % 16) < 10)
			g_num[index] = x % 16 + '0';
		else
			g_num[index] = x % 16 - 10 + reg;
		x /= 16;
		index--;
	}
	if ((x % 16) < 10)
		g_num[index] = x % 16 + '0';
	else
		g_num[index] = x % 16 - 10 + reg;
}

void	handle_x(int var, t_print *tab)
{
	unsigned long long	x;

	tab->var = var;
	ulong_init(&x, tab);
	g_len = count_hex(x);
	in_hex(x, var);
	if (!x && !tab->prec && !tab->width)
		return ;
	if (tab->flags[3] == '-')
		x_minflag(x, g_len, g_num, tab);
	else if (tab->flags[0] == '0' && tab->prec == -1)
		x_zeroflag(x, g_len, g_num, tab);
	else
		x_noflag(x, g_len, g_num, tab);
}
