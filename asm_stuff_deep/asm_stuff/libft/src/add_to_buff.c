/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_buff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:40:54 by marius            #+#    #+#             */
/*   Updated: 2022/04/05 15:52:05 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	add_str_to_buff(char *str, t_print *tab)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		add_to_buff(str[index], tab);
		index++;
	}
}

void	add_to_buff(char c, t_print *tab)
{
	tab->buff[tab->printed++] = c;
	if (!(tab->index % BUFF_SIZE))
	{
		ft_putstr(tab->buff);
		ft_bzero(&tab->buff, 4096);
		tab->ret = tab->ret + tab->printed;
		tab->printed = 0;
	}
}

static size_t	count(unsigned long long n)
{
	size_t	i;

	i = 0;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*abs_itoa_long(unsigned long long n)
{
	char	*str;
	int		len;

	len = 2 + count(n);
	str = (char *)malloc(sizeof(char) * len);
	str[--len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
