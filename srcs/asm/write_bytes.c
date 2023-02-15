/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:05:48 by parkharo          #+#    #+#             */
/*   Updated: 2023/02/15 21:32:43 by parkharo         ###   ########.fr       */
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

void	write_null(int count_bytes, int fd)
{
	int	var;

	var = 0;
	while (count_bytes--)
		write(fd, &var, 1);
}

void	write_bytes(int fd, int input, int count_bytes)
{
	char	*arr;
	int		i;

	i = 0;
	if (input == 0)
	{
		write_null(count_bytes, fd);
		return ;
	}
	arr = ft_strnew(count_bytes);
	int32_to_bytecode(arr, input, count_bytes);
	while (i < count_bytes)
		write(fd, &arr[i++], 1);
	free(arr);
}
