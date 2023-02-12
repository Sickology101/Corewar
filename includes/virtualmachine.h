/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtualmachine.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:24:57 by marius            #+#    #+#             */
/*   Updated: 2023/01/30 17:30:54 by mtissari         ###   ########.fr       */
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
	int					last_live;
	int					lives_amount;
	const char			*path;
	const char			*name;
	const char			*comment;
	size_t				exec_size;
	uint8_t				*exec_code;
	struct s_player		*next;

}					t_player;

typedef struct s_counter
{
	int				cycles_total;
	int				cycles_to_die;
	int				cycles_after_check;
	int				checks_total;
	int				lives_this_period;
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
	size_t				rel_pos;
	int32_t				reg[REG_NUMBER];
	t_player			*player;
	struct s_process	*next;
}						t_process;

typedef struct s_data
{
	struct s_counter	counter;
	t_player			*player;
	int					last_alive;
	int					dump_cycles;
	int					player_amount;
	uint8_t				arena[MEM_SIZE];
	size_t				process_amount;
	struct s_process	*process_head;
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
	uint8_t		carry_mod;
	void		(*func)(t_data *const, t_process *);
}				t_statement;

void		exit_error_message(char *message);

/*-------Prints-------*/

void		print_introduction(t_data *const data);
void		print_arena(t_data *const data);

/*-------Inits--------*/

void		init_data(t_data *data);
void		init_player(const char *path, t_player **player, int flag_id);
void		init_arena(t_data *const data);

/*-------Player_ids---*/

void		check_amount_of_players(t_data *const data);
void		set_players_ids(t_data *const data);
void		sort_players_list(t_data *const data);

/*-------Read_players---*/

void		validate_user_input(const int ac, const char **av,
				t_data *const data);

/*-------Flags----------*/

void		check_n_flag_unique_ids(t_data *const data);
int			validate_and_receive_n_flag(int *i, const char **av, int ac);
void		validate_and_receive_dump_flag_arg(int *i, const char **av, int ac,
				t_data *const data);

/*-------Validation-----*/

int			validate_player(t_data *const data);

/*-------Player_code_validation*/

void		get_exec_code(int fd, t_player *player);
void		check_null_separator(int fd);
void		get_champion_comment(int fd, t_player *player);

/*-------Vm_Utils-------*/

int			swap_endians(int buffer);
int32_t		read_bytes(uint8_t *arena, int cur_pos, int size);
int32_t		read_4_bytes(uint8_t *arena, int cur_pos);
void		move_rel_pos(int arg_type, t_process *carr, t_statement *op);

// void	put_reg_value_on_arena(uint8_t *arena, int value, int pos);
void		put_reg_value_on_arena(uint8_t *arena, int value,
				int pos, int size);
void		set_carry(t_process *carriage, int arg);

/*-------Get_arguments--------*/

int			get_arg(t_data *const data, t_process *carr, int arg_num, int idx);

/*-------Process--------*/

void		free_process(t_process *process);
void		create_initial_process_list(t_data *const data);
t_process	*copy_process(t_data *const data, t_process *carriage, int pos);

/*-------Game_loop------*/

void		run_game_loop(t_data *const data);

/*-------Set_statements------*/

void		perform_cycle(t_data *const data);
void		move_process(t_process *carriage);

/*-------Statements------*/

void		set_add(t_data *const data, t_process *carriage);
void		set_aff(t_data *const data, t_process *carriage);
void		set_and(t_data *const data, t_process *carriage);
void		set_fork(t_data *const data, t_process *carriage);
void		set_ldi(t_data *const data, t_process *carriage);
void		set_lfork(t_data *const data, t_process *carriage);
void		set_live(t_data *const data, t_process *carriage);
void		set_lld(t_data *const data, t_process *carriage);
void		set_lldi(t_data *const data, t_process *carriage);
void		set_ld(t_data *const data, t_process *carriage);
void		set_or(t_data *const data, t_process *carriage);
void		set_st(t_data *const data, t_process *carriage);
void		set_sti(t_data *const data, t_process *carriage);
void		set_sub(t_data *const data, t_process *carriage);
void		set_xor(t_data *const data, t_process *carriage);
void		set_zjmp(t_data *const data, t_process *carriage);

/*-------Execute--------*/

void		execute_statement(t_data *const data, t_process *carriage);
void		load_value_to_reg(t_process *carriage, int value, int reg_num);

static uint8_t			g_arg_code[3] = {
	T_REG,
	T_DIR,
	T_IND
};

static t_statement		g_op[16] = {
{
	.name = "live",
	.id = 1,
	.cycles_num = 10,
	.args_num = 1,
	.args = {T_DIR},
	.read_types = 0,
	.tdir_size = 4,
	.carry_mod = 0,
	.func = &set_live
},
{
	.name = "ld",
	.id = 2,
	.cycles_num = 5,
	.args_num = 2,
	.args = {T_DIR | T_IND, T_REG},
	.read_types = 1,
	.tdir_size = 4,
	.carry_mod = 1,
	.func = &set_ld
},
{
	.name = "st",
	.id = 3,
	.cycles_num = 5,
	.args_num = 2,
	.args = {T_REG, T_IND | T_REG},
	.read_types = 1,
	.tdir_size = 4,
	.carry_mod = 0,
	.func = &set_st
},
{
	.name = "add",
	.id = 4,
	.cycles_num = 10,
	.args_num = 3,
	.args = {T_REG, T_REG, T_REG},
	.read_types = 1,
	.tdir_size = 4,
	.carry_mod = 1,
	.func = &set_add
},
{
	.name = "sub",
	.id = 5,
	.cycles_num = 10,
	.args_num = 3,
	.args = {T_REG, T_REG, T_REG},
	.read_types = 1,
	.tdir_size = 4,
	.carry_mod = 1,
	.func = &set_sub
},
{
	.name = "and",
	.id = 6,
	.cycles_num = 6,
	.args_num = 3,
	.args = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
	.read_types = 1,
	.tdir_size = 4,
	.carry_mod = 1,
	.func = &set_and
},
{
	.name = "or",
	.id = 7,
	.cycles_num = 6,
	.args_num = 3,
	.args = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
	.read_types = 1,
	.tdir_size = 4,
	.carry_mod = 1,
	.func = &set_or
},
{
	.name = "xor",
	.id = 8,
	.cycles_num = 6,
	.args_num = 3,
	.args = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
	.read_types = 1,
	.tdir_size = 4,
	.carry_mod = 1,
	.func = &set_xor
},
{
	.name = "zjmp",
	.id = 9,
	.cycles_num = 20,
	.args_num = 1,
	.args = {T_DIR},
	.read_types = 0,
	.tdir_size = 2,
	.carry_mod = 0,
	.func = &set_zjmp
},
{
	.name = "ldi",
	.id = 10,
	.cycles_num = 25,
	.args_num = 3,
	.args = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
	.read_types = 1,
	.tdir_size = 2,
	.carry_mod = 0,
	.func = set_ldi
},
{
	.name = "sti",
	.id = 11,
	.cycles_num = 25,
	.args_num = 3,
	.args = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
	.read_types = 1,
	.tdir_size = 2,
	.carry_mod = 0,
	.func = &set_sti
},
{
	.name = "fork",
	.id = 12,
	.cycles_num = 800,
	.args_num = 1,
	.args = {T_DIR},
	.read_types = 0,
	.tdir_size = 2,
	.carry_mod = 0,
	.func = &set_fork
},
{
	.name = "lld",
	.id = 13,
	.cycles_num = 10,
	.args_num = 2,
	.args = {T_DIR | T_IND, T_REG},
	.read_types = 1,
	.tdir_size = 4,
	.carry_mod = 1,
	.func = &set_lld
},
{
	.name = "lldi",
	.id = 14,
	.cycles_num = 50,
	.args_num = 3,
	.args = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
	.read_types = 1,
	.tdir_size = 2,
	.carry_mod = 1,
	.func = &set_lldi
},
{
	.name = "lfork",
	.id = 15,
	.cycles_num = 1000,
	.args_num = 1,
	.args = {T_DIR},
	.read_types = 0,
	.tdir_size = 2,
	.carry_mod = 0,
	.func = &set_lfork
},
{
	.name = "aff",
	.id = 16,
	.cycles_num = 2,
	.args_num = 1,
	.args = {T_REG},
	.read_types = 1,
	.tdir_size = 4,
	.carry_mod = 0,
	.func = &set_aff
},
};

#endif
