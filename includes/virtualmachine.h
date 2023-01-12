/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtualmachine.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:24:57 by marius            #+#    #+#             */
/*   Updated: 2023/01/08 14:26:19 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUALMACHINE_H
# define VIRTUALMACHINE_H

# include "../libft/includes/ft_printf.h"
# include <stdbool.h>

typedef struct s_player
{
	int				id;
	const char			*path;
	// const char			*name;
	const char			*comment;
	struct s_player	*next;

}					t_player;

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

#endif
