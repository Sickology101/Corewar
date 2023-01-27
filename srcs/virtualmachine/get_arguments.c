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
	int16_t	ind;
	int		ret;

	printf("\t\tARG: |%i| CODE: |%i|\n\n", args, code);
	ret = 0;
	if (code == IND_CODE)
	{
		ind = args;
		ind = ind % IDX_MOD;
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
		ret = args - 1;
	}
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

int	get_arg(t_data *const data, t_process *carriage, int pos, int arg_code)
{
	t_statement	*op;
	int			arg;

	op = &g_op[carriage->op_id - 1];
	printf("pos: %i, data->arena[pos] + op->read_types: %i\n\n", pos, (data->arena[pos] + op->read_types));
	if (arg_code == DIR_CODE)
		arg = set_dir(data->arena,
				pos + op->read_types, op->tdir_size);
	else if (arg_code == IND_CODE)
		arg = set_ind(data->arena, pos);
	else
		arg = calculate_args(REG_CODE, data->arena[pos]);
	return (arg);
}
