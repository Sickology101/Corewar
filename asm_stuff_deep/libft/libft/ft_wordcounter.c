/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcounter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:20:20 by marius            #+#    #+#             */
/*   Updated: 2022/05/28 16:22:38 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wordcounter(const char *str, char c)
{
	int	i;
	int	wcount;
	int	state;

	i = 0;
	wcount = 0;
	state = 0;
	while (str[i])
	{
		if (c == str[i])
			state = 0;
		else if (state == 0)
		{
			state = 1;
			wcount++;
		}
		i++;
	}
	return (wcount);
}
