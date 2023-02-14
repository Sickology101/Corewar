# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marius <marius@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 10:11:17 by marius            #+#    #+#              #
#    Updated: 2023/02/14 09:32:02 by marius           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR		=	corewar
ASSEMBLER	=	assembler
LIBFT		=	libft/libftprintf.a
FLAGS		=	-Wall -Wextra -Werror -I includes -I libft/includes -I libft/libft #-g -fsanitize=address

SRC		=	main.c scanner.c get_name_comment.c utils.c get_instructions.c get_statements.c write_to_file.c write_bytes.c joinfree.c populate.c get_statements2.c get_statements3.c get_statements4.c populate_help.c write_utils.c

LIBFT_DIR	=	libft/
SRC_DIR		=	srcs/asm/

CHK_SRCS	=	$(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR		=	obj/
OBJS		= 	$(SRC_OBJS)
SRC_OBJS	=	$(patsubst %, $(OBJ_DIR)%, $(SRC:.c=.o))

all: $(COREWAR)

$(COREWAR): $(LIBFT) $(OBJ_DIR) $(SRC_OBJS)
	@gcc $(FLAGS) $(LIBFT) $(SRC_OBJS) -o $(ASSEMBLER)
	@printf "Compilation complete.\n"
	
$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@gcc $(FLAGS) -o $@ -c $<
	@printf "Corewar compiled.\n"

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS) $(SURPL_O)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME) *.out

re: fclean all