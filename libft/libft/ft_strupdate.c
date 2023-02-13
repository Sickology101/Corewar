/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupdate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:19:15 by marius            #+#    #+#             */
/*   Updated: 2023/02/13 15:21:30 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strupdate(char *s1, const char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	free(s1);
	return (temp);
}
