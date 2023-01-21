/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:03 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/21 16:38:13 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/virtualmachine.h"

void	set_fork(t_data *const data, t_process *carriage)
{
	carriage->operation_code = 12;
	carriage->cycles_before_exec = 800;
	printf("\n\n\t\tyou've reached set_fork\n");
}
