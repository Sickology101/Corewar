# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marius <marius@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 10:11:17 by marius            #+#    #+#              #
#    Updated: 2023/01/16 15:29:28 by marius           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR		=	corewar
ASSEMBLER	=	assembler
LIBFT		=	libft/libftprintf.a
FLAGS		=	-Wall -Wextra -Werror -I includes -I libft/includes -I libft/libft

SRC		=	main.c scanner.c init_statements.c name_checker.c

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