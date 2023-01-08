/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangheli <mangheli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:57:21 by mangheli          #+#    #+#             */
/*   Updated: 2021/11/08 16:57:23 by mangheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_islower(int c)
{
	if (c > 96 && c < 123)
		return (1);
	else
		return (0);
}

static	int	ft_isupper(int c)
{
	if (c > 64 && c < 91)
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if (ft_isupper(c) != 0 || ft_islower(c) != 0)
		return (1);
	else
		return (0);
}
