/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_statements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:13:12 by marius            #+#    #+#             */
/*   Updated: 2023/01/28 03:53:16 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*static t_statements	init_live(void)
{
	t_statements	s;

	s.str = ft_strdup("live");
	s.arg_num = 1;
	s.arg = (int *)malloc(sizeof(int));
	s.arg[0] = T_DIR; // 2
	return (s);
}

static t_statements	init_ld(void)
{
	t_statements	s;

	s.str = ft_strdup("ld");
	s.arg_num = 2;
	s.arg = (int *)malloc(sizeof(int) * 2);
	s.arg[0] = T_DIR + T_IND;
	s.arg[1] = T_REG;
	return (s);
}

static t_statements	init_st(void)
{
	t_statements	s;

	s.str = ft_strdup("st");
	s.arg_num = 2;
	s.arg = (int *)malloc(sizeof(int) * 2);
	s.arg[0] = T_REG;
	s.arg[1] = T_REG + T_IND;
	return (s);
}

static t_statements	init_add(void)
{
	t_statements	s;

	s.str = ft_strdup("add");
	s.arg_num = 3;
	s.arg = (int *)malloc(sizeof(int) * 3);
	s.arg[0] = T_REG;
	s.arg[1] = T_REG;
	s.arg[2] = T_REG;
	return (s);
}

static t_statements	init_sub(void)
{
	t_statements	s;

	s.str = ft_strdup("sub");
	s.arg_num = 3;
	s.arg = (int *)malloc(sizeof(int) * 3);
	s.arg[0] = T_REG;
	s.arg[1] = T_REG;
	s.arg[2] = T_REG;
	return (s);
}

static t_statements	init_and(void)
{
	t_statements	s;

	s.str = ft_strdup("and");
	s.arg_num = 3;
	s.arg = (int *)malloc(sizeof(int) * 3);
	s.arg[0] = T_REG + T_IND + T_DIR;
	s.arg[1] = T_REG + T_IND + T_DIR;
	s.arg[2] = T_REG;
	return (s);
}

static t_statements	init_or(void)
{
	t_statements	s;

	s.str = ft_strdup("or");
	s.arg_num = 3;
	s.arg = (int *)malloc(sizeof(int) * 3);
	s.arg[0] = T_REG + T_IND + T_DIR;
	s.arg[1] = T_REG + T_IND + T_DIR;
	s.arg[2] = T_REG;
	return (s);
}

static t_statements	init_xor(void)
{
	t_statements	s;

	s.str = ft_strdup("xor");
	s.arg_num = 3;
	s.arg = (int *)malloc(sizeof(int) * 3);
	s.arg[0] = T_REG + T_IND + T_DIR;
	s.arg[1] = T_REG + T_IND + T_DIR;
	s.arg[2] = T_REG;
	return (s);
}

static t_statements	init_zjmp(void)
{
	t_statements	s;

	s.str = ft_strdup("zjmp");
	s.arg_num = 1;
	s.arg = (int *)malloc(sizeof(int) * 1);
	s.arg[0] = T_DIR;
	return (s);
}

static t_statements	init_ldi(void)
{
	t_statements	s;

	s.str = ft_strdup("ldi");
	s.arg_num = 3;
	s.arg = (int *)malloc(sizeof(int) * 3);
	s.arg[0] = T_REG + T_IND + T_DIR;
	s.arg[1] = T_REG + T_DIR;
	s.arg[2] = T_REG;
	return (s);
}

static t_statements	init_sti(void)
{
	t_statements	s;

	s.str = ft_strdup("sti");
	s.arg_num = 3;
	s.arg = (int *)malloc(sizeof(int) * 3);
	s.arg[0] = T_REG;
	s.arg[1] = T_REG + T_DIR + T_IND;
	s.arg[2] = T_REG + T_DIR;
	return (s);
}

static t_statements	init_fork(void)
{
	t_statements	s;

	s.str = ft_strdup("fork");
	s.arg_num = 1;
	s.arg = (int *)malloc(sizeof(int) * 1);
	s.arg[0] = T_DIR;
	return (s);
}

static t_statements	init_lld(void)
{
	t_statements	s;

	s.str = ft_strdup("lld");
	s.arg_num = 2;
	s.arg = (int *)malloc(sizeof(int) * 2);
	s.arg[0] = T_DIR + T_IND;
	s.arg[1] = T_REG;
	return (s);
}

static t_statements	init_lldi(void)
{
	t_statements	s;

	s.str = ft_strdup("lldi");
	s.arg_num = 3;
	s.arg = (int *)malloc(sizeof(int) * 3);
	s.arg[0] = T_REG + T_DIR + T_IND; // 1 + 2 + 4 = 7
	s.arg[1] = T_REG + T_DIR; // 1 + 2 = 3
	s.arg[2] = T_REG; // 1
	return (s);
}

static t_statements	init_lfork(void)
{
	t_statements	s;

	s.str = ft_strdup("lfork");
	s.arg_num = 1;
	s.arg = (int *)malloc(sizeof(int) * 1);
	s.arg[0] = T_DIR;
	return (s);
}

static t_statements	init_aff(void)
{
	t_statements	s;

	s.str = ft_strdup("aff");
	s.arg_num = 1;
	s.arg = (int *)malloc(sizeof(int) * 1);
	s.arg[0] = T_REG;
	return (s);
}

// this initializes the statements array with all the valid statements and allowed args
void	init_statements(t_parser *data)
{
	data->s = (t_statements *)malloc(sizeof(t_statements) * 16);
	data->s[0] = init_live();
	data->s[1] = init_ld();
	data->s[2] = init_st();
	data->s[3] = init_add();
	data->s[4] = init_sub();
	data->s[5] = init_and();
	data->s[6] = init_or();
	data->s[7] = init_xor();
	data->s[8] = init_zjmp();
	data->s[9] = init_ldi();
	data->s[10] = init_sti();
	data->s[11] = init_fork();
	data->s[12] = init_lld();
	data->s[13] = init_lldi();
	data->s[14] = init_lfork();
	data->s[15] = init_aff();
}
*/