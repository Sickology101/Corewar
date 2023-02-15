/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:17:13 by marius            #+#    #+#             */
/*   Updated: 2022/04/06 10:45:21 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	clean_all(t_print *tab)
{
	ft_bzero(tab->flags, sizeof(char) * 5);
	tab->width = 0;
	tab->prec = -1;
	ft_bzero(tab->length, 3);
	tab->type = 0;
	tab->var = 0;
}

static	void	init_tab(t_print *tab)
{
	tab->index = 0;
	tab->printed = 0;
	tab->ret = 0;
	tab->buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
}

static void	handle_arg2(t_print *tab)
{
	if (tab->type == 'c')
		handle_c(tab);
	if (tab->type == 's')
		handle_s(tab);
	if (tab->type == 'p')
		handle_p(tab);
	if (tab->type == 'd' || tab->type == 'i')
		handle_d_i(tab);
	if (tab->type == 'o')
		handle_o(tab);
	if (tab->type == 'u')
		handle_u(tab);
	if (tab->type == 'x')
		handle_x(0, tab);
	if (tab->type == 'X')
		handle_x(1, tab);
	if (tab->type == 'f')
		handle_f(tab);
	if (tab->type == '%')
		handle_proc(tab);
}

void	handle_arg(const char *format, t_print *tab)
{
	clean_all(tab);
	add_flags(format, tab);
	add_width(format, tab);
	add_prec(format, tab);
	add_length(format, tab);
	if (format[tab->index] == 'c' || format[tab->index] == 's'
		|| format[tab->index] == 'p' || format[tab->index] == 'd'
		|| format[tab->index] == 'i' || format[tab->index] == 'o'
		|| format[tab->index] == 'u' || format[tab->index] == 'x'
		|| format[tab->index] == 'X' || format[tab->index] == 'f'
		|| format[tab->index] == '%')
	{
		tab->type = format[tab->index];
		tab->index++;
	}
	handle_arg2(tab);
}

int	ft_printf(const char *format, ...)
{
	size_t	printed;
	t_print	*tab;

	tab = (t_print *)malloc(sizeof(t_print));
	init_tab(tab);
	va_start(tab->args, format);
	while (format[tab->index] != '\0')
	{
		if (format[tab->index] == '%')
			handle_arg(format, tab);
		else
			add_to_buff(format[tab->index++], tab);
	}
	va_end(tab->args);
	tab->buff[tab->printed] = '\0';
	ft_putstr(tab->buff);
	if (tab->ret == 0)
		printed = tab->printed;
	else
		printed = tab->ret + tab->printed;
	free(tab->buff);
	free(tab);
	return (printed);
}
