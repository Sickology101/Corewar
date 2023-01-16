/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:25:13 by marius            #+#    #+#             */
/*   Updated: 2023/01/16 20:26:58 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

// this function ignores empty lines
bool	check_empty_line(char *str)
{
	if (str[0] == '\0')
		return (true);
	else
		return (false);
}