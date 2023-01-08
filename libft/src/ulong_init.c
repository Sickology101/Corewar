/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulong_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:08:51 by marius            #+#    #+#             */
/*   Updated: 2022/04/06 10:10:20 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ulong_init(unsigned long long *a, t_print *tab)
{
	if (!(ft_strcmp(tab->length, "l")))
		*a = va_arg(tab->args, unsigned long);
	else if (!(ft_strcmp(tab->length, "ll")))
		*a = va_arg(tab->args, unsigned long long);
	else if (!(ft_strcmp(tab->length, "h")))
		*a = (unsigned short)va_arg(tab->args, unsigned int);
	else if (!(ft_strcmp(tab->length, "hh")))
		*a = (unsigned char)va_arg(tab->args, unsigned int);
	else
		*a = va_arg(tab->args, unsigned int);
}
