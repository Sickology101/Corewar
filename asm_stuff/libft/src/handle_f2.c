/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_f2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:41:46 by marius            #+#    #+#             */
/*   Updated: 2022/05/29 16:42:48 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	g_index1;
static int	g_index2;
static int	g_min;
static char	*g_big;
static int	g_dot;
static int	*g_calc_num;
static int	g_op;

int	is_nan(long double d)
{
	return ((d != d) || (((d) < 0) == ((d) > 0)));
}

int	is_inf(long double d)
{
	if ((is_nan(d - d)) && 10 - d == -d && d > 0)
		return (1);
	else if ((is_nan(d - d)) && 10 - d == -d && d < 0)
		return (-1);
	else
		return (0);
}

static void	add_to_int_arr(long double f, t_print *tab)
{
	while (g_index1 < ALLOC_SIZE)
	{
		f *= 10;
		g_op = (int)f;
		f -= g_op;
		g_calc_num[g_index1] = g_op;
		g_index1++;
	}
	g_index1 = ALLOC_SIZE - 1;
	while (g_index1 > tab->prec + g_dot - 1)
	{
		if (g_calc_num[g_index1] > 4)
			g_calc_num[g_index1 - 1]++;
		g_calc_num[g_index1] = 0;
		g_index1--;
	}
	while (g_index1 > 0)
	{
		if (g_calc_num[g_index1] > 9)
		{
			g_calc_num[g_index1 - 1]++;
			g_calc_num[g_index1] = 0;
		}
		g_index1--;
	}
}

static void	add_to_char_arr(char **num, t_print *tab)
{
	g_index1 = 0;
	g_index2 = 0;
	*num = (char *)malloc(sizeof(char) * (g_min + g_dot + tab->prec + 1));
	(*num)[g_min + g_dot + tab->prec] = '\0';
	if (g_min)
		(*num)[g_index2++] = '-';
	while (g_index1 < g_dot)
	{
		if (g_calc_num[g_index1] > 9)
			(*num)[g_index2++] = g_calc_num[g_index1++] / 10 + '0';
		(*num)[g_index2++] = g_calc_num[g_index1++] + '0';
	}
	if (tab->prec || (!tab->prec && tab->flags[4] == '#'))
		(*num)[g_index2++] = '.';
	while (g_index1 - g_dot < tab->prec)
	{
		if (g_index1 >= ALLOC_SIZE)
		{
			(*num)[g_index2++] = '0';
			g_index1++;
		}
		else
			(*num)[g_index2++] = g_calc_num[g_index1++] % 10 + '0';
	}
}

void	in_double(char **num, long double f, t_print *tab)
{
	if (f < 0)
	{
		g_min = 1;
		f = -f;
	}
	else
		g_min = 0;
	if (tab->prec == -1)
		tab->prec = 6;
	g_calc_num = (int *)malloc(sizeof(int) * ALLOC_SIZE);
	g_big = abs_itoa_long(f);
	g_index1 = 0;
	while (g_big[g_index1] != '\0')
	{
		g_calc_num[g_index1] = g_big[g_index1] - '0';
		g_index1++;
	}
	g_dot = g_index1;
	f -= (unsigned long long)f;
	add_to_int_arr(f, tab);
	add_to_char_arr(num, tab);
	free(g_calc_num);
}
