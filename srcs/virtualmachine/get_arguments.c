/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:58:02 by mtissari          #+#    #+#             */
/*   Updated: 2023/02/09 19:12:41 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

int32_t	read_4_bytes(uint8_t *arena, int read_pos)
{
	int32_t	res;
	int		sign;

	sign = arena[read_pos % MEM_SIZE] & 0x80;
	res = 0;
	if (!sign)
		res = arena[read_pos % MEM_SIZE] << 24
			| arena[(read_pos + 1) % MEM_SIZE] << 16
			| arena[(read_pos + 2) % MEM_SIZE] << 8
			| arena[(read_pos + 3) % MEM_SIZE];
	else
		res = (arena[read_pos % MEM_SIZE] ^ 0xFF) << 24
			| (arena[(read_pos + 1) % MEM_SIZE] ^ 0xFF) << 16
			| (arena[(read_pos + 2) % MEM_SIZE] ^ 0xFF) << 8
			| (arena[(read_pos + 3) % MEM_SIZE] ^ 0xFF);
	if (sign)
		res = ~(res);
	return (res);
}

int16_t	read_2_bytes(uint8_t *arena, int cur_pos)
{
	int32_t	res;
	int		sign;

	sign = arena[cur_pos % MEM_SIZE] & 0x80;
	res = 0;
	if (!sign)
		res = arena[cur_pos % MEM_SIZE] << 8
			| arena[(cur_pos + 1) % MEM_SIZE];
	else
		res = (arena[cur_pos % MEM_SIZE] ^ 0xFF) << 8
			| (arena[(cur_pos + 1) % MEM_SIZE] ^ 0xFF);
	if (sign)
		res = ~(res);
	return (res);
}

int32_t	read_bytes(uint8_t *arena, int read_pos, int size)
{
	int32_t	res;

	res = 0;
	if (size == 2)
		res = read_2_bytes(arena, read_pos);
	else if (size == 4)
		res = read_4_bytes(arena, read_pos);
	return (res);
}

void	move_rel_pos(int arg_type, t_process *carr, t_statement *op)
{
	if (arg_type == T_DIR)
		carr->rel_pos += op->tdir_size;
	else if (arg_type == T_IND)
		carr->rel_pos += 2;
	else
		carr->rel_pos += 1;
}

int	get_arg(t_data *const data, t_process *carr, int arg_num, int idx)
{
	t_statement	*op;
	int			arg;
	int			real_pos;

	real_pos = (carr->cur_pos + carr->rel_pos) % MEM_SIZE;
	op = &g_op[carr->op_id - 1];
	if (carr->args[arg_num] == T_DIR)
		arg = read_bytes(data->arena, real_pos, op->tdir_size);
	else if (carr->args[arg_num] == T_IND)
	{
		arg = read_2_bytes(data->arena, real_pos);
		if (idx == 0)
			arg = read_bytes(data->arena,
					(carr->cur_pos + arg) % MEM_SIZE, DIR_SIZE);
		else
			arg = read_bytes(data->arena,
					(carr->cur_pos + (arg % idx)) % MEM_SIZE, DIR_SIZE);
	}
	else
		arg = carr->reg[data->arena[real_pos] - 1];
	move_rel_pos(carr->args[arg_num], carr, op);
	return (arg);
}
