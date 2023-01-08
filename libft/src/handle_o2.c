/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_o2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:41:13 by marius            #+#    #+#             */
/*   Updated: 2022/04/05 15:36:17 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	oct_count(unsigned long long o)
{
	int	i;

	i = 1;
	while (o / 8)
	{
		o /= 8;
		i++;
	}
	return (i);
}

void	in_octave(char **dec, unsigned long long o)
{
	int	len;
	int	i;

	len = oct_count(o);
	*dec = (char *)malloc(sizeof(char) * (len + 1));
	(*dec)[len] = '\0';
	i = len - 1;
	while (o / 8)
	{
		(*dec)[i] = o % 8 + '0';
		o /= 8;
		i--;
	}
	(*dec)[i] = o % 8 + '0';
}
