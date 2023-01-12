/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtualmachine.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:24:57 by marius            #+#    #+#             */
/*   Updated: 2023/01/12 17:44:45 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUALMACHINE_H
# define VIRTUALMACHINE_H

# include "../libft/includes/ft_printf.h"
# include <stdbool.h>

#define MEM_SIZE				(4*1024)

typedef struct s_player
{
	int					id;
	int					fd;
	const char			*path;
	const char			*name;
	const char			*comment;
	int					exec_size;
	uint8_t				*exec_code;
	struct s_player	*next;

}					t_player;

typedef struct s_counter
{
	int			total_cycles;
	int			nbr_live;
}				t_counter;

typedef struct s_data
{
	t_player		*player;
	int				player_amount;
	uint8_t			arena[MEM_SIZE];
}					t_data;


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
int		validate_and_receive_n_flag_arg(int *i, const char **av, int ac);
void	validate_user_input(const int ac, const char **av, t_data * const data);

/*-------Validation-----*/
int		validate_player(t_data *const data);


#endif
