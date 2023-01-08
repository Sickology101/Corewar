/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:45:00 by marius            #+#    #+#             */
/*   Updated: 2022/04/11 11:18:24 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	count(unsigned long long p)
{
	int	count;

	count = 0;
	while (p > 0)
	{
		count++;
		p /= 16;
	}
	return (count);
}

static char	*hex_to_alph(char *dest, unsigned long long p)
{
	unsigned int	len;
	unsigned int	index;
	unsigned int	mod;

	len = count(p) + 1;
	index = len - 2;
	while (p > 0)
	{
		mod = p % 16;
		if (mod >= 10)
			dest[index--] = (mod -10) + 'a';
		else
			dest[index--] = mod + '0';
		p /= 16;
	}
	dest[len - 1] = '\0';
	return (dest);
}

static char	*address_hex(unsigned long long p, t_print *tab)
{
	char	*str;
	char	*dest;

	dest = ft_strnew(16);
	str = ft_strnew(12);
	if (!str && !dest)
	{
		return (0);
	}
	if (p == 0)
	{
		if (tab->prec > 0)
			ft_memset(str, '0', tab->prec);
		else
			ft_memset(str, '0', 1);
	}
	else
		str = hex_to_alph(str, p);
	ft_strcpy(dest, "0x");
	if (tab->prec != 0)
		ft_strcpy(&dest[2], str);
	ft_strdel(&str);
	return (dest);
}

static void	p_print(char *addr, t_print *tab)
{
	int	index;

	index = tab->width - ft_strlen(addr);
	if (tab->flags[3] == '-')
	{
		add_str_to_buff(addr, tab);
		while (index > 0)
		{
			add_to_buff(' ', tab);
			index--;
		}
	}
	else
	{
		while (index > 0)
		{
			add_to_buff(' ', tab);
			index--;
		}
		add_str_to_buff(addr, tab);
	}
}

void	handle_p(t_print *tab)
{
	unsigned long long	p;
	char				*addr;

	p = va_arg(tab->args, unsigned long long);
	addr = address_hex(p, tab);
	if (tab->width > ft_strlen(addr))
		p_print(addr, tab);
	else
		add_str_to_buff(addr, tab);
	free (addr);
}
