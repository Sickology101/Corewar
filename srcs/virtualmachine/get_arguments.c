/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:58:02 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/27 19:48:29 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

/*
** Calculate_args converts the unsigned ints to signed int16_t's,
** which is the way we get the negatives when we need them.
*/
int	calculate_args(int code, int args)
{
	int		ret;
	char	*str;

	str = NULL;
	if (code == 1)
		str = "T_REG";
	else if (code == 2)
		str = "T_DIR";
	else if (code == 3)
		str = "T_IND";
	ret = args;
	if (code == REG_CODE)
	{
		if (args < 1 || args > 16) // invalid reg, just ignore and skip?
			return (-1); // will probably segfault with this>need to fix
	}
	printf("\t\tARG: |%i| CODE: |%s|\n\n", ret, str);
	return (ret);
}

int16_t	read_2_bytes(uint8_t *arena, int cur_pos, int sign)
{
	int16_t	res;

	sign = arena[cur_pos] & 0x80;
	res = 0;
	if (!sign)
		res = arena[cur_pos % MEM_SIZE] << 8
			| arena[(cur_pos + 1) % MEM_SIZE];
	else
		res = ((arena[cur_pos % MEM_SIZE] ^ 0xFF) << 8)
			| (arena[(cur_pos + 1) % MEM_SIZE] ^ 0xFF);
	if (sign)
		res = ~(res);
	return (res);
}

int32_t	read_4_bytes(uint8_t *arena, int cur_pos, int sign)
{
	int32_t	res;

	sign = arena[cur_pos] & 0x80;
	res = 0;
	if (!sign)
		res = arena[cur_pos % MEM_SIZE] << 24
			| arena[(cur_pos + 1) % MEM_SIZE] << 16
			| arena[(cur_pos + 2) % MEM_SIZE] << 8
			| arena[(cur_pos + 3) % MEM_SIZE];
	else
		res = (arena[cur_pos % MEM_SIZE] ^ 0xFF) << 24
			| (arena[(cur_pos + 1) % MEM_SIZE] ^ 0xFF) << 16
			| (arena[(cur_pos + 2) % MEM_SIZE] ^ 0xFF) << 8
			| (arena[(cur_pos + 3) % MEM_SIZE] ^ 0xFF);
	if (sign)
		res = ~(res);
	return (res);
}

int32_t	read_bytes(uint8_t *arena, int cur_pos, int size, int code)
{
	int sign;
	int	res;

	res = 0;
	sign = arena[cur_pos] &0x80;
	if (size == 2)
		res = read_2_bytes(arena, cur_pos, sign);
	else
		res = read_4_bytes(arena, cur_pos, sign);
	res = calculate_args(code, res);
	return (res);
}

int	get_arg(t_data *const data, t_process *carriage, size_t *rel_pos, int arg_num)
{
	t_statement	*op;
	int			arg;
	int			real_pos;	

	real_pos = (carriage->cur_pos + *rel_pos) % MEM_SIZE;
	op = &g_op[carriage->op_id - 1];
	printf("\tcarriage at: %zu, reading bytes from: %i tdir_size: %d\n\n", carriage->cur_pos, real_pos, g_op[carriage->op_id - 1].tdir_size);
	if (carriage->args[arg_num] == DIR_CODE)
	{
		arg = read_bytes(data->arena, real_pos, op->tdir_size, DIR_CODE);
		*rel_pos += op->tdir_size;
	}
	else if (carriage->args[arg_num] == IND_CODE)
	{
		arg = read_bytes(data->arena, real_pos, IND_SIZE, IND_CODE);
		*rel_pos += IND_SIZE;
	}
	else
	{
		arg = calculate_args(REG_CODE, data->arena[real_pos]);
		arg = carriage->reg[arg - 1];
		*rel_pos += 1;
	}
	return (arg);
}
