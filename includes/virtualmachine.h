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

typedef struct s_player
{
	int					id;
	int					fd;
	const char			*path;
	const char			*name;
	const char			*comment;
	int					exec_size;
	int					exec_code;
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
}					t_data;


void	init_data(t_data *data);
void	exit_error_message(char *message);
void	validate_user_input(const int ac, const char **av, t_data * const data);
int		validate_and_receive_n_flag_arg(int *i, const char **av, int ac);
void	check_amount_of_players(t_data *const data);
void	set_players_ids(t_data *const data);
void	sort_players_list(t_data *const data);
int		validate_player(t_data *const data);
void	init_player(const char *path, t_player **player, int flag_id);
void	print_introduction(t_data *const data);
void	print_champion_path_and_id(t_data *const data);

#endif
