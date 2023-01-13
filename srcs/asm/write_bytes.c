/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:05:48 by parkharo          #+#    #+#             */
/*   Updated: 2023/01/13 18:08:35 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "assembler.h"

void	write_bytes(int fd, int input, int count_bytes)
{
	int				original_count;
	unsigned char	arr[count_bytes];

	original_count = count_bytes;
	while (count_bytes--)
	{
		arr[count_bytes] = (unsigned char)input;
		input >>= 8;
	}
	while (++count_bytes < original_count)
		write(fd, &arr[count_bytes], 1);
}
