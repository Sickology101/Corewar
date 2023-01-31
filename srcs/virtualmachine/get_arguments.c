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
	int32_t	ind;
	int		ret;
	char	*str;

	str = NULL;
	if (code == 1)
		str = "T_REG";
	else if (code == 2)
		str = "T_DIR";
	else if (code == 3)
		str = "T_IND";
	ret = 0;
	if (code == IND_CODE)
	{
		ind = args;
		ret = ind;
	}
	else if (code == DIR_CODE)
	{
		ret = args;
	}
	else if (code == REG_CODE)
	{
		if (args < 1 || args > 16) // invalid reg, just ignore and skip?
			return (-1); // will probably segfault with this>need to fix
		ret = args;
	}
	printf("\t\tARG: |%i| CODE: |%s|\n\n", ret, str);
	return (ret);
}

int	set_dir(uint8_t *arena, int pos, int dir_size)
{
	int	new;

	new = make_dir_to_int(arena, pos, dir_size);
	new = calculate_args(DIR_CODE, new);
	return (new);
}

int	set_ind(uint8_t *arena, int pos)
{
	int	new;

	new = make_ind_to_int(arena, pos);
	new = calculate_args(IND_CODE, new);
	return (new);
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
		arg = set_dir(data->arena, real_pos, op->tdir_size);
		*rel_pos += op->tdir_size;
	}
	else if (carriage->args[arg_num] == IND_CODE)
	{
		arg = set_ind(data->arena, real_pos);
		*rel_pos += T_IND;
	}
	else
	{
		arg = calculate_args(REG_CODE, data->arena[real_pos]);
		arg = carriage->reg[arg - 1];
		*rel_pos += T_REG;
	}
	return (arg);
}
