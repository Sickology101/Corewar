/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:05:48 by parkharo          #+#    #+#             */
/*   Updated: 2023/02/04 13:51:58 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	int32_to_bytecode(char *data,
							int32_t value,
							size_t size)
{
	int8_t		i;

	i = 0;
	while (size)
	{
		data[size - 1] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

void	write_bytes(int fd, int input, int count_bytes)
{
	char	*arr;
	int		i;

	i = 0;
	arr = ft_strnew(count_bytes);
	int32_to_bytecode(arr, input, count_bytes);
	while (i < count_bytes)
		write(fd, &arr[i++], 1);
	free(arr);
}
