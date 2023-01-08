# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marius <marius@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 10:11:17 by marius            #+#    #+#              #
#    Updated: 2023/01/08 14:22:29 by marius           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc

NAME=libftprintf.a 

FLAGS= -Wall -Wextra -Werror -g
SRC_PATH=./src/
SRC_FILES=ft_printf.c \
	ft_vasprintf.c \
	num_conversion.c \
	percent_parse.c \
	width_precision_parse.c \
	precision_f.c \
	print_c.c \
	print_d.c \
	print_f.c \
	print_f2.c \
	print_o.c \
	print_p.c\
	print_perc.c\
	print_str.c \
	print_uxX.c \
	build_result.c

SRC=$(addprefix $(SRC_PATH), $(SRC_FILES))

OBJ_PATH=./obj/
OBJ_FILES=$(SRC_FILES:.c=.o)
OBJ=$(addprefix $(OBJ_PATH), $(OBJ_FILES))

LIB_OBJ_PATH=./libft/
LIB_OBJ=$(LIB_SRC:.c=.o)

LIB_SRC_PATH=./libft/
LIB_SRC=$(addprefix $(LIB_SRC_PATH), $(LIB_SRC_FILES))
LIB_SRC_FILES=ft_strlen.c \
	ft_strcpy.c \
	ft_putchar.c \
	ft_strdup.c \
	ft_putnbr.c \
	ft_putstr.c \
	ft_atoi.c \
	ft_isalpha.c \
	ft_isalnum.c \
	ft_isdigit.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strncpy.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strcmp.c \
	ft_strstr.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strcat.c \
	ft_strncat.c \
	ft_strlcat.c \
	ft_strrchr.c \
	ft_strdel.c \
	ft_strclr.c \
	ft_strnew.c \
	ft_memalloc.c \
	ft_memdel.c \
	ft_putendl.c \
	ft_strequ.c \
	ft_strnequ.c \
	ft_strsub.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_strsplit.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_itoa.c \
	ft_lstnew.c \
	ft_lstadd.c \
	ft_lstiter.c \
	ft_lstdelone.c \
	ft_lstdel.c \
	ft_lstmap.c \
	ft_print_double.c \
	ft_isspace.c \
	ft_lstadd_end.c \
	ft_lstlen.c \
	ft_lstmerge.c \
	ft_atoi_base.c \
	get_next_line.c \
	ft_itoa_base.c \
	ft_numlenbase.c \
	ft_uitoa_base.c \
	ft_unumlenbase.c

INCLUDES=-I./includes -I./libft
HEADERS_PATH=./includes/
HEADERS_FILES=ft_printf.h
HEADERS=$(addprefix $(HEADERS_PATH), $(HEADERS_FILES))

all: $(NAME) 

$(NAME): $(OBJ) $(LIB_OBJ) $(HEADERS) 
	@ar rc $(NAME) $(OBJ) $(LIB_OBJ)
	@ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2>/dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(LIB_OBJ_PATH)%.o: $(LIB_SRC_PATH)%.c
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make -C ./libft clean
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)

fclean: clean
	@make -C ./libft fclean
	@rm -f $(NAME)

re: fclean all clean all

.PHONY: clean fclean re all

