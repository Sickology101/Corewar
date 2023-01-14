/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_code_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:34:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/14 20:38:46 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	get_exec_code(int fd, t_player *player)
{
	int		rtn;
	char	buffer[CHAMP_MAX_SIZE];

	rtn = read(fd, buffer, player->exec_size);
	printf("\tbytes read in get_exec_code: %i\n\n", rtn);
	printf("\033[0;32m executable CODE: %s\n\n\033[0m", buffer);
	if (rtn < (int)player->exec_size)
	{
		exit_error_message("invalid champion name");
	}
	if (buffer[0])
	{
		player->exec_code = (uint8_t *)malloc(sizeof(uint8_t) * rtn);
		ft_memcpy(player->exec_code, buffer, player->exec_size);
	}
	else
		printf("\t\tbuffer[0](in exec code) does not exist...\n");
}

void	check_null_separator(int fd)
{
	int		rtn;
	int		buffer;

	rtn = read(fd, &buffer, 4);
	if (rtn < 4 || buffer != 0)
	{
		exit_error_message("invalid NULL");
	}
	printf("\tbytes read in chehk_null_separator: %i\n\n", rtn);
}

void	get_champion_comment(int fd, t_player *player)
{
	int		rtn;
	char	buffer[COMMENT_LENGTH];

	rtn = lseek(fd, 0, SEEK_CUR);
	printf("CURRENT LOCATION: %i\n", rtn);
	rtn = read(fd, buffer, COMMENT_LENGTH);
	printf("\tbytes read in get_champion_comment: %i\n\n", rtn);
	if (rtn < COMMENT_LENGTH)
	{
		exit_error_message("invalid champion comment");
	}
	if (buffer[0])
		player->comment = ft_strdup(buffer);
	else
		printf("\033[0;93m \t\tbuffer[0]"
			"(champion comment) does not exist...\n \033[0m");
	printf("\033[0;32m CHAMPION "
		"COMMENT: %s\n\n \033[0m", player->comment);
	check_null_separator(fd);
}
