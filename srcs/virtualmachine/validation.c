/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:40:34 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/14 20:35:04 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

void	get_exec_size(int fd, t_player *player)
{
	int		rtn;
	int		buffer;

	rtn = lseek(fd, 0, SEEK_CUR);
	if (rtn != 136)
		exit_error_message("Error: Wrong byte location");
	printf("CURRENT LOCATION: %i\n", rtn);
	rtn = read(fd, &buffer, 4);
	if (rtn < 4)
		exit_error_message("invalid file");
	buffer = swap_endians(buffer);
	if (buffer > CHAMP_MAX_SIZE)
		exit_error_message("invalid exec_size");
	player->exec_size = buffer;
	printf("\033[0;32m executable SIZE: %zu\n\033[0m", player->exec_size);
}

void	get_champion_name(int fd, t_player *player)
{
	int		rtn;
	char	buffer[PROG_NAME_LENGTH];

	rtn = read(fd, buffer, PROG_NAME_LENGTH);
	if (rtn < PROG_NAME_LENGTH)
		exit_error_message("Error reading!");
	printf("\tbytes read in get_champion_name: %i\n\n", rtn);
	printf("\033[0;32m CHAMPION NAME: %s\n\n\033[0m", buffer);
	if (ft_strlen(buffer) > PROG_NAME_LENGTH)
	{
		exit_error_message("invalid champion name");
	}
	if (buffer[0])
		player->name = ft_strdup(buffer);
	check_null_separator(fd);
}

void	check_magic_header(int fd)
{
	int		rtn;
	int		buffer;

	rtn = read(fd, &buffer, 4);
	if (rtn < 4)
		exit_error_message("Error reading!");
	buffer = swap_endians(buffer);
	if (buffer != COREWAR_EXEC_MAGIC)
		exit_error_message("invalid magic header");
}

int	validate_player(t_data *const data)
{
	int			fd;
	int			rtn;
	int			delete;
	t_player	*player;

	player = data->player;
	while (player)
	{
		fd = open(player->path, O_RDONLY);
		player->fd = fd;
		check_magic_header(fd);
		get_champion_name(fd, player);
		get_exec_size(fd, player);
		get_champion_comment(fd, player);
		get_exec_code(fd, player);
		rtn = 1;
		while (rtn >= 1)
		{
			rtn = read(fd, &delete, 1);
			printf(" %i rounds until EOF\n", rtn);
		}
		printf("--------------------------------------");
		close (fd); // We'll see later if it needs to stay open.
		player = player->next;
	}
	return (0);
}

/*   _______________________________________________________
	| an empty string can also be used as a champion name:  |
	|														|
	| .name ""												|
	| But the complete absence of a string is an error:		|
	|														|
	| .name													|
	|_______________________________________________________|
		^ This has not been dealt with yet!!
*/
