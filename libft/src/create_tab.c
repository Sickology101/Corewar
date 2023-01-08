/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:22:47 by marius            #+#    #+#             */
/*   Updated: 2022/05/29 16:42:16 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	add_flags(const char *format, t_print *tab)
{
	tab->index++;
	while (1)
	{
		if (format[tab->index] == '0')
			tab->flags[0] = format[tab->index];
		else if (format[tab->index] == ' ')
			tab->flags[1] = format[tab->index];
		else if (format[tab->index] == '+')
			tab->flags[2] = format[tab->index];
		else if (format[tab->index] == '-')
			tab->flags[3] = format[tab->index];
		else if (format[tab->index] == '#')
			tab->flags[4] = format[tab->index];
		else
			break ;
		tab->index++;
	}
}

void	add_width(const char *format, t_print *tab)
{
	int	val;

	tab->width = ft_atoi(&(format[tab->index]));
	if (tab->width)
		while ('0' <= format[tab->index] && format[tab->index] <= '9')
			tab->index++;
	else if (format[tab->index] == '*')
	{
		val = va_arg(tab->args, int);
		if (val < 0)
		{
			tab->width = -val;
			tab->flags[3] = '-';
		}
		else
			tab->width = val;
		tab->index++;
	}
}

void	add_prec(const char *format, t_print *tab)
{
	if (format[tab->index] == '.')
	{
		tab->index++;
		tab->prec = ft_atoi(&(format[tab->index]));
		if (tab->prec)
			while ('0' <= format[tab->index] && format[tab->index] <= '9')
				tab->index++;
		else if (format[tab->index] == '*')
		{
			tab->prec = va_arg(tab->args, int);
			tab->index++;
		}
		else if (format[tab->index] == '0')
		{
			tab->prec = 0;
			tab->index++;
		}
		else
			tab->prec = 0;
	}
}

void	add_length(const char *format, t_print *tab)
{
	if (format[tab->index] == 'L')
	{
		tab->length[0] = 'L';
		tab->index++;
	}
	else if (format[tab->index] == 'l')
	{
		tab->length[0] = 'l';
		if (format[tab->index + 1] == 'l')
		{
			tab->length[1] = 'l';
			tab->index++;
		}
		tab->index++;
	}
	else if (format[tab->index] == 'h')
	{
		tab->length[0] = 'h';
		if (format[tab->index + 1] == 'h')
		{
			tab->length [1] = 'h';
			tab->index++;
		}
		tab->index++;
	}
}
