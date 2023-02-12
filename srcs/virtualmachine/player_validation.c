/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:40:34 by mtissari          #+#    #+#             */
/*   Updated: 2023/02/09 19:16:49 by mtissari         ###   ########.fr       */
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
	rtn = read(fd, &buffer, 4);
	if (rtn < 4)
		exit_error_message("Error reading - Champion file to short!");
	buffer = swap_endians(buffer);
	if (buffer > CHAMP_MAX_SIZE)
	{
		ft_printf("Error: File %s has too large a code (%d bytes > %d bytes)\n",
			player->path, buffer, CHAMP_MAX_SIZE);
		exit(0);
	}
	else
		player->exec_size = buffer;
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
	if ((buffer[0] && ft_strlen(buffer) > PROG_NAME_LENGTH))
	{
		exit_error_message("\033[0;93m invalid champion name");
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
	int			file_checker;
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
		rtn = read(fd, &file_checker, 1);
		if (rtn > 0)
			exit_error_message("invalid file");
		close (fd);
		player = player->next;
	}
	return (0);
}
