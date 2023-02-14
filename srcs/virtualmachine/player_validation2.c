/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_validation2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:34:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/02/14 18:13:53 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

/*
** get_exec_code reads and saves the code in the t_player-struct.
*/
void	get_exec_code(int fd, t_player *player)
{
	int		rtn;
	char	buffer[CHAMP_MAX_SIZE];

	rtn = read(fd, buffer, player->exec_size);
	if (rtn < 1)
	{
		player->exec_code = (uint8_t *)malloc(sizeof(uint8_t) * 1);
		if (!player->exec_code)
			exit_error_message("player->exec_code allocation failed!");
		ft_memcpy(player->exec_code, buffer, player->exec_size);
	}
	else if (buffer[0])
	{
		player->exec_code = (uint8_t *)malloc(sizeof(uint8_t) * rtn);
		if (!player->exec_code)
			exit_error_message("player->exec_code allocation failed!");
		ft_memcpy(player->exec_code, buffer, player->exec_size);
	}
}

/*
** check_null_separator validates that there are 4 NULL bytes after champion
** name and after champion comment.
*/
void	check_null_separator(int fd)
{
	int		rtn;
	int		buffer;

	rtn = read(fd, &buffer, 4);
	if (rtn < 4 || buffer != 0)
	{
		exit_error_message("invalid NULL - champion name or comment too long");
	}
}

/*
** get_champion_comment validates the length if the comment and saves it.
*/
void	get_champion_comment(int fd, t_player *player)
{
	int		rtn;
	char	buffer[COMMENT_LENGTH + 1];

	buffer[COMMENT_LENGTH] = '\0';
	rtn = read(fd, buffer, COMMENT_LENGTH);
	if (rtn < COMMENT_LENGTH)
		exit_error_message("invalid champion comment");
	if (buffer[0])
		player->comment = ft_strdup(buffer);
	else
		player->comment = ft_strdup("");
	check_null_separator(fd);
}
