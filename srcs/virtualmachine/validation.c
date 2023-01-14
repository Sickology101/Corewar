/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:40:34 by mtissari          #+#    #+#             */
/*   Updated: 2023/01/12 17:41:10 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/virtualmachine.h"
#include "../../resources_42/op.h"

void	exit_error(char *str)	//Just for testing purposes, delete this!
{
	printf("%s\n", str);
	exit(0);
}

int	swap_endians(int buffer)
{
	int	leftmost;
	int	left_middle;
	int	right_middle;
	int	rightmost;

	leftmost = (buffer & 0x000000FF) >> 0;
	left_middle = (buffer & 0x0000FF00) >> 8;
	right_middle = (buffer & 0x00FF0000) >> 16;
	rightmost = (buffer & 0xFF000000) >> 24;
	leftmost <<= 24;
	left_middle <<= 16;
	right_middle <<= 8;
	rightmost <<= 0;
	return (leftmost | left_middle | right_middle | rightmost);
}

void	get_exec_code(int fd, t_player *player)
{
	int		rtn;
	char	buffer[CHAMP_MAX_SIZE];

	rtn = read(fd, buffer, player->exec_size);
	printf("\tbytes read in get_exec_code: %i\n\n", rtn);
	printf("\033[0;32m executable CODE: %s\n\n\033[0m", buffer);
	if (rtn < (int)player->exec_size)
	{
		exit_error("invalid champion name");
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
		exit_error("invalid NULL");
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
		exit_error("invalid champion comment");
	}
	if (buffer[0])
		player->comment = ft_strdup(buffer);
	else
		printf("\033[0;93m \t\tbuffer[0](champion comment) does not exist...\n \033[0m");
	printf("\033[0;32m CHAMPION COMMENT: %s\n\n \033[0m", player->comment);
	check_null_separator(fd);
}

void	get_exec_size(int fd, t_player *player)
{
	int		rtn;
	int		buffer;

	rtn = lseek(fd, 0, SEEK_CUR);				//DONT FORGET WE CAN'T USE IT, CAN WE??
	if (rtn != 136)
		exit_error("Error: Wrong byte location");//Might have to do differently
	printf("CURRENT LOCATION: %i\n", rtn);
	rtn = read(fd, &buffer, 4);
	if (rtn < 4)
		exit_error("invalid file");
	buffer = swap_endians(buffer);
	if (buffer > CHAMP_MAX_SIZE)
		exit_error("invalid exec_size");
	player->exec_size = buffer;
	printf("\033[0;32m executable SIZE: %zu\n\033[0m", player->exec_size);
}

void	get_champion_name(int fd, t_player *player)
{
	int		rtn;
	char	buffer[PROG_NAME_LENGTH];

	rtn = read(fd, buffer, PROG_NAME_LENGTH);
	if (rtn < PROG_NAME_LENGTH)
		exit_error("Error reading!");
	printf("\tbytes read in get_champion_name: %i\n\n", rtn);
	printf("\033[0;32m CHAMPION NAME: %s\n\n\033[0m", buffer);
	if (ft_strlen(buffer) > PROG_NAME_LENGTH)
	{
		exit_error("invalid champion name");
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
		exit_error("Error reading!");
	buffer = swap_endians(buffer);
	if (buffer != COREWAR_EXEC_MAGIC)
		exit_error("invalid magic header");
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
		player->fd = fd; 						//just in case
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
		close (fd);	// We'll see later if it needs to stay open.
		player = player->next;
	}
	return (0);
}
/*											THESE WERE FOR (local)TESTINGG!!!
void	free_player(t_player *player)
{
	if (player)
	{
		if (player->name)
			free(player->name);
		if (player->comment)
			free (player->comment);
		if (player->exec_code)
			free (player->exec_code);
		if (player->next)
			free (player->next);
		free (player);
	}
}

t_player	*init_player(void)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
	{
		printf("ERROR: malloc error in t_player\n");
		exit(0);
	}
	player->name = NULL;
	player->comment = NULL;
	player->id = 0;
	player->exec_size = 0;
	player->exec_code = NULL;
	player->next = NULL;
	return (player);
}*/

// int	main(int argc, char **argv)
// {
// 	t_player	*player;

// 	player = init_player();
// 	validate_player(argv[1], player);
// 	free_player (player);
// 	printf("\033[1;95mALLES GOTT?\n");
// 	return (0);
// }

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
