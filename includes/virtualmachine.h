/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtualmachine.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:24:57 by marius            #+#    #+#             */
/*   Updated: 2023/01/19 18:23:36 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUALMACHINE_H
# define VIRTUALMACHINE_H

# include "../libft/includes/ft_printf.h"
# include <stdbool.h>
# include <stdint.h>
# include "op.h"

typedef struct s_player
{
	int					id;
	const char			*path;
	const char			*name;
	const char			*comment;
	size_t				exec_size;
	uint8_t				*exec_code;
	struct s_player		*next;

}					t_player;

typedef struct s_counter
{
	int			total_cycles;
	int			cycles_to_die;
	int			nb_of_checks_done;
	int			checks_without_reducing;
	int			lives_this_period;
	int			initial_cycles;
}				t_counter;

typedef struct s_process
{
	size_t				unique_id;
	int					carry;
	uint8_t				op_id;
	int					last_live;
	int					cycles_before_exec;
	uint8_t				args[3];
	size_t				cur_pos;
	size_t				next_operation;
	size_t				reg[REG_NUMBER];
	t_player			*player;
	struct s_process	*next;
}						t_process;

typedef struct s_data
{
	struct s_counter	counter;
	t_player			*player;
	t_player			*last_alive;
	int					dump_cycles;
	int					player_amount;
	uint8_t				arena[MEM_SIZE];
	size_t				process_amount;
	struct s_process	*process_head;
	struct s_process	*process_tail;
}						t_data;

typedef struct s_statement
{
	char		*name;
	uint8_t		id;
	uint16_t	cycles_num;
	uint8_t		args_num;
	uint8_t		args[3];
	uint8_t		read_types;
	uint8_t		tdir_size;
	void		(*func)(t_data *const, t_process *);
}				t_statement;

void	exit_error_message(char *message);

/*-------Prints-------*/

void	print_introduction(t_data *const data);
void	print_player_code(t_player *player);
void	print_champion_path_and_id(t_data *const data);
void	print_arena(t_data *const data);

/*-------Inits--------*/

void	init_data(t_data *data);
void	init_player(const char *path, t_player **player, int flag_id);
void	init_arena(t_data *const data);

/*-------Player_ids---*/

void	check_amount_of_players(t_data *const data);
void	set_players_ids(t_data *const data);
void	sort_players_list(t_data *const data);

/*-------Read_players---*/

void	validate_user_input(const int ac, const char **av, t_data *const data);

/*-------Flags----------*/

void	check_n_flag_unique_ids(t_data *const data);
int		validate_and_receive_n_flag(int *i, const char **av, int ac);
void	validate_and_receive_dump_flag_arg(int *i, const char **av, int ac,
			t_data *const data);

/*-------Validation-----*/

int		validate_player(t_data *const data);

/*-------Player_code_validation*/

void	get_exec_code(int fd, t_player *player);
void	check_null_separator(int fd);
void	get_champion_comment(int fd, t_player *player);

/*-------Vm_Utils-------*/

int		swap_endians(int buffer);

/*-------Process--------*/

void	create_initial_process_list(t_data *const data);

/*-------Game_loop------*/

void	run_game_loop(t_data *const data);

/*-------Set_statements------*/

void	set_statement_codes(t_data *const data, t_process *carriage);
void	perform_cycle(t_data *const data);

/*-------Check_statement------*/

void	check_statement(t_data *const data, t_process *carriage);

/*-------Statements------*/

void	set_add(t_data *const data, t_process *carriage);
void	set_aff(t_data *const data, t_process *carriage);
void	set_and(t_data *const data, t_process *carriage);
void	set_fork(t_data *const data, t_process *carriage);
void	set_ldi(t_data *const data, t_process *carriage);
void	set_lfork(t_data *const data, t_process *carriage);
void	set_live(t_data *const data, t_process *carriage);
void	set_lld(t_data *const data, t_process *carriage);
void	set_lldi(t_data *const data, t_process *carriage);
void	set_ld(t_data *const data, t_process *carriage);
void	set_or(t_data *const data, t_process *carriage);
void	set_st(t_data *const data, t_process *carriage);
void	set_sti(t_data *const data, t_process *carriage);
void	set_sub(t_data *const data, t_process *carriage);
void	set_xor(t_data *const data, t_process *carriage);
void	set_zjmp(t_data *const data, t_process *carriage);

/*-------Execute--------*/

void	execute_statement(t_data *const data, t_process *carriage);

static t_statement	g_op[16]
	=	{
{
	.name = "live",
	.id = 1,
	.cycles_num = 10,
	.args_num = 1,
	.args = {DIR_CODE},
	.read_types = 0,
	.tdir_size = 4,
	.func = &set_live
},
{
	.name = "ld",
	.id = 2,
	.cycles_num = 5,
	.args_num = 2,
	.args = {DIR_CODE | IND_CODE, REG_CODE},
	.read_types = 1,
	.tdir_size = 4,
	.func = &set_ld
},
{
	.name = "st",
	.id = 3,
	.cycles_num = 5,
	.args_num = 2,
	.args = {REG_CODE, IND_CODE | REG_CODE},
	.read_types = 1,
	.tdir_size = 4,
	.func = &set_st
},
{
	.name = "add",
	.id = 4,
	.cycles_num = 10,
	.args_num = 3,
	.args = {REG_CODE, REG_CODE, REG_CODE},
	.read_types = 1,
	.tdir_size = 4,
	.func = &set_add
},
{
	.name = "sub",
	.id = 5,
	.cycles_num = 10,
	.args_num = 3,
	.args = {REG_CODE, REG_CODE, REG_CODE},
	.read_types = 1,
	.tdir_size = 4,
	.func = &set_sub
},
{
	.name = "and",
	.id = 6,
	.cycles_num = 6,
	.args_num = 3,
	.args = {REG_CODE | DIR_CODE | IND_CODE, REG_CODE | IND_CODE | DIR_CODE, REG_CODE},
	.read_types = 1,
	.tdir_size = 4,
	.func = &set_and
},
{
	.name = "or",
	.id = 7,
	.cycles_num = 6,
	.args_num = 3,
	.args = {REG_CODE | IND_CODE | DIR_CODE, REG_CODE | IND_CODE | DIR_CODE, REG_CODE},
	.read_types = 1,
	.tdir_size = 4,
	.func = &set_or
},
{
	.name = "xor",
	.id = 8,
	.cycles_num = 6,
	.args_num = 3,
	.args = {REG_CODE | IND_CODE | DIR_CODE, REG_CODE | IND_CODE | DIR_CODE, REG_CODE},
	.read_types = 1,
	.tdir_size = 4,
	.func = &set_xor
},
{
	.name = "zjmp",
	.id = 9,
	.cycles_num = 20,
	.args_num = 1,
	.args = {DIR_CODE},
	.read_types = 0,
	.tdir_size = 2,
	.func = &set_zjmp
},
{
	.name = "ldi",
	.id = 10,
	.cycles_num = 25,
	.args_num = 3,
	.args = {REG_CODE | DIR_CODE | IND_CODE, DIR_CODE | REG_CODE, REG_CODE},
	.read_types = 1,
	.tdir_size = 2,
	.func = set_ldi
},
{
	.name = "sti",
	.id = 11,
	.cycles_num = 25,
	.args_num = 3,
	.args = {REG_CODE, REG_CODE | DIR_CODE | IND_CODE, DIR_CODE | REG_CODE},
	.read_types = 1,
	.tdir_size = 2,
	.func = &set_sti
},
{
	.name = "fork",
	.id = 12,
	.cycles_num = 800,
	.args_num = 1,
	.args = {DIR_CODE},
	.read_types = 0,
	.tdir_size = 2,
	.func = &set_fork
},
{
	.name = "lld",
	.id = 13,
	.cycles_num = 10,
	.args_num = 2,
	.args = {DIR_CODE | IND_CODE, REG_CODE},
	.read_types = 1,
	.tdir_size = 4,
	.func = &set_lld
},
{
	.name = "lldi",
	.id = 14,
	.cycles_num = 50,
	.args_num = 3,
	.args = {REG_CODE | DIR_CODE | IND_CODE, DIR_CODE | REG_CODE, REG_CODE},
	.read_types = 1,
	.tdir_size = 2,
	.func = &set_lldi
},
{
	.name = "lfork",
	.id = 15,
	.cycles_num = 1000,
	.args_num = 1,
	.args = {DIR_CODE},
	.read_types = 0,
	.tdir_size = 2,
	.func = &set_lfork
},
{
	.name = "aff",
	.id = 16,
	.cycles_num = 2,
	.args_num = 1,
	.args = {REG_CODE},
	.read_types = 1,
	.tdir_size = 4,
	.func = &set_aff
},
};

#endif
