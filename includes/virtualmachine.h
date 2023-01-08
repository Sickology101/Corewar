/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtualmachine.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:24:57 by marius            #+#    #+#             */
/*   Updated: 2023/01/11 18:50:44 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUALMACHINE_H
# define VIRTUALMACHINE_H

# include "../libft/includes/ft_printf.h"
# include <stdbool.h>

typedef struct s_player
{
	int				id;
	const char			*name;
	const char			*comment;
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
}					t_data;


void	init_data(t_data *data);
void	exit_error_message(char *message);
void	open_players(const int ac, const char **av, t_data * const data);

#endif
