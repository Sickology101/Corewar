/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:05:48 by parkharo          #+#    #+#             */
/*   Updated: 2023/02/02 08:34:42 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "assembler.h"

// void	write_bytes(int fd, int input, int count_bytes)
// {
// 	int				original_count;
// 	unsigned char	arr[count_bytes];

// 	original_count = count_bytes;
// 	while (count_bytes--)
// 	{
// 		arr[count_bytes] = (unsigned char)input;
// 		input >>= 8;
// 	}
// 	while (++count_bytes < original_count)
// 		write(fd, &arr[count_bytes], 1);
// }

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
	//int				original_count;
	char	arr[count_bytes];

	int32_to_bytecode(arr, input, count_bytes);
	// original_count = count_bytes;
	// while (count_bytes--)
	// {
	// 	arr[count_bytes] = (unsigned char)input;
	// 	input >>= 8;
	// }
	int i = 0;
	while (i < count_bytes) //< original_count)
		write(fd, &arr[i++], 1);
}