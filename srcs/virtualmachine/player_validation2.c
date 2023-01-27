/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_code_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:34:11 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/27 16:26:24 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

/*
** get_exec_code reads and saves the code in the t_player-struct.
** !!!!! (and checks if it exists? not sure if it needs to exist?) !!!!!
*/
void	get_exec_code(int fd, t_player *player)
{
	int		rtn;
	char	buffer[CHAMP_MAX_SIZE];

	rtn = read(fd, buffer, player->exec_size);
	printf("\tbytes read in get_exec_code: %i\n\n", rtn);
	printf("\033[0;32m executable CODE: %s\n\n\033[0m", buffer);
	if (rtn < 1)
	{
		/* NEED TO DISCUSS IF THIS IS AN ERROR! */
		exit_error_message("No executable code detected");
	}
	if (buffer[0])
	{
		player->exec_code = (uint8_t *)malloc(sizeof(uint8_t) * rtn);
		ft_memcpy(player->exec_code, buffer, player->exec_size);
	}
	else
		printf("\t\tbuffer[0](in exec code) does not exist...\n");
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
	printf("\tbytes read in chehk_null_separator: %i\n\n", rtn);
}

/*
** get_champion_comment validates the length if the comment and saves it.
*/
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
		printf("\033[0;93m \t\tbuffer[0]" // An error or not?
			"(champion comment) does not exist...\n \033[0m");
	printf("\033[0;32m CHAMPION "
		"COMMENT: %s\n\n \033[0m", player->comment);
	check_null_separator(fd);
}
