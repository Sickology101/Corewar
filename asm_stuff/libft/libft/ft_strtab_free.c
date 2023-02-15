/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:48:38 by marius            #+#    #+#             */
/*   Updated: 2022/05/29 16:40:33 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtab_free(char **strtab)
{
	int	i;

	i = -1;
	while (strtab[++i] != NULL)
		free(strtab[i]);
	free(strtab);
}
