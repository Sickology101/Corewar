/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:40:34 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/26 17:33:37 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"

/*
** get_exec_size reads 4 bytes that include the size of the executable code
** in bytes. It cannot exceed CHAMP_MAX_SIZE, but there is no minimum limit,
** hence in the case the size is 0, we set it to CHAMP_MAX_SIZE.
*/
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
		exit_error_message("Error reading - Champion file to short!");
	buffer = swap_endians(buffer);
	if (buffer > CHAMP_MAX_SIZE)
		exit_error_message("invalid exec_size");
	else if (buffer == 0)
	{
		/* THIS IS IN VALIDATION PART IN COOKBOOK - VIRTUAL MACHINE */
		player->exec_size = CHAMP_MAX_SIZE;
	}
	else
		player->exec_size = buffer;
	printf("\033[0;32m executable SIZE: %zu\n\033[0m", player->exec_size);
}

/*
** get_champion_name validates the name length and saves it
*/
void	get_champion_name(int fd, t_player *player)
{
	int		rtn;
	char	buffer[PROG_NAME_LENGTH];

	rtn = read(fd, buffer, PROG_NAME_LENGTH);
	if (rtn < PROG_NAME_LENGTH)
		exit_error_message("Error reading - Champion file to short!");
	printf("\tbytes read in get_champion_name: %i\n\n", rtn);
	printf("\033[0;32m CHAMPION NAME: %s\n\n\033[0m", buffer);
	if (!buffer[0] || ft_strlen(buffer) > PROG_NAME_LENGTH)
	{
		exit_error_message("invalid champion name");
	}
	player->name = ft_strdup(buffer);
	check_null_separator(fd);
}

/*
** Check_magic_header reads the first 4 bytes of the file and checks if the
** magic header in the file is valid.
*/
void	check_magic_header(int fd)
{
	int		rtn;
	int		buffer;

	rtn = read(fd, &buffer, 4);
	if (rtn < 4)
		exit_error_message("Error reading -  file to short!");
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
		if (fd < 0)
			exit_error_message("Error opening a file!");
		check_magic_header(fd);
		get_champion_name(fd, player);
		get_exec_size(fd, player);
		get_champion_comment(fd, player);
		get_exec_code(fd, player);
		rtn = 1;
		while (rtn >= 1)
		{
			rtn = read(fd, &delete, 1); //if this is > 0, file is too long?
			printf(" %i rounds until EOF\n", rtn); // so is it an error then?
		}
		printf("--------------------------------------");
		close (fd);
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
		Let's see if it needs to be validated here
*/
