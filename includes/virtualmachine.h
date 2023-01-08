/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtualmachine.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:24:57 by marius            #+#    #+#             */
/*   Updated: 2023/01/08 19:01:17 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUALMACHINE_H

# define VIRTUALMACHINE_H

# include "../libft/includes/ft_printf.h"

typedef struct s_counter
{
	int					total_cycles;
	int					nbr_live;
	int					cycle_to_die;
	int					cycle_delta;
	int					max_checks;
}						t_counter;

typedef struct s_data
{
	struct s_counter	counter;
	
}						t_data;

#endif
