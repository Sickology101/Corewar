# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marius <marius@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/15 08:10:42 by marius            #+#    #+#              #
#    Updated: 2022/04/05 16:07:17 by marius           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re mfclean mre

NAME		=	libftprintf.a
SRC_D		=	src/
OBJ_D		=	.obj/

LIB			=	libft/
LIB_N		=	libft.a

SRC			=	ft_printf add_to_buff create_tab handle_c handle_d_i handle_f handle_f2 handle_o handle_o2 handle_p handle_proc handle_s handle_u handle_x handle_x2 ulong_init
SRCS		=	$(addprefix $(SRC_D), $(addsuffix .c, $(SRC)))
OBJ			=	$(addprefix $(OBJ_D), $(SRCS:%.c=%.o))
INCLUDE		=	-I includes/ -I $(LIB)

CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_D) $(OBJ)
	make -C $(LIB)
	cp $(LIB)$(LIB_N) $(NAME)
	ar -r $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_D):
	mkdir -p $(OBJ_D)$(SRC_D)

$(OBJ_D)%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	make clean -C $(LIB)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIB)
	rm -f $(NAME)
	rm -rf $(OBJ_D)

re: fclean all

test: fclean all
	$(CC) -o main $(INCLUDE) $(NAME) main.c
	./main