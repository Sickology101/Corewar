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
]CYELLOW=\033[0;33m
CEND=\033[0m
CGREEN=\033[0;32m

CC = gcc
VM_NAME = corewar
FLAGS = -g -Wall -Wextra #-Werror

VM_SRC_DIR = ./srcs/virtualmachine/
VM_SRC_FILES = main.c \
				read_players.c \
				n_flag.c
VM_SRC = $(addprefix $(VM_SRC_DIR), $(VM_SRC_FILES))

VM_OBJ_DIR = ./vm_obj/
VM_OBJ_FILES = $(VM_SRC_FILES:.c=.o)
VM_OBJ = $(addprefix $(VM_OBJ_DIR), $(VM_OBJ_FILES))

VM_INC_DIR = ./includes/
VM_INC_FILES = virtualmachine.h
VM_INC = $(addprefix $(VM_INC_DIR), $(VM_INC_FILES))

LIBFT_DIR = libft/
LIBFT_LIB = libftprintf.a
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_LIB))

all : $(VM_NAME)

$(VM_NAME): $(VM_OBJ) $(VM_INC)
	@make -C $(LIBFT_DIR)
	@echo "$(CYELLOW)Compiling $(VM_NAME)$(CEND)"
	@$(CC) -o $(VM_NAME) $(FLAGS) $(VM_OBJ) -I libft/includes/ -I ./includes/ -L. $(LIBFT)
	@echo "$(CGREEN)OK$(CEND)"

$(VM_OBJ_DIR)%.o: $(VM_SRC_DIR)%.c
	@mkdir -p $(VM_OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

clean :
	@make -C $(LIBFT_DIR) clean
	@echo "$(CYELLOW)Removing $(VM_NAME) object folder$(CEND)"
	@rm -rf $(VM_OBJ_DIR)
	@echo "$(CGREEN)OK$(CEND)"

fclean : clean
	@make -C $(LIBFT_DIR) fclean
	@echo "$(CYELLOW)Removing $(VM_NAME)$(CEND)"
	@rm -rf $(VM_NAME)
	@echo "$(CGREEN)OK$(CEND)"

re : fclean all clean all

# COREWAR		=	corewar
# ASSEMBLER	=	assembler
# LIBFT		=	libft/libftprintf.a
# FLAGS		=	-Wall -Wextra -Werror -I includes -I libft/includes -I libft/libft

# VM_SRC		=	

# LIBFT_DIR	=	libft/
# VM_SRC_DIR		=	srcs/

# CHK_SRCS	=	$(addprefix $(VM_SRC_DIR), $(VM_SRC))

# VM_OBJ_DIR		=	obj/
# OBJS		= 	$(SRC_OBJS)
# SRC_OBJS	=	$(patsubst %, $(VM_OBJ_DIR)%, $(VM_SRC:.c=.o))

# all: $(COREWAR)

# $(COREWAR): $(LIBFT) $(VM_OBJ_DIR) $(SRC_OBJS)
# 	@gcc $(FLAGS) $(LIBFT) $(SRC_OBJS) -o $(VM_NAME)
# 	@printf "Compilation complete.\n"
	
# $(LIBFT):
# 	@make -C $(LIBFT_DIR)

# $(VM_OBJ_DIR):
# 	@mkdir -p $(VM_OBJ_DIR)

# $(VM_OBJ_DIR)%.o: $(VM_SRC_DIR)%.c
# 	@gcc $(FLAGS) -o $@ -c $<
# 	@printf "Corewar compiled.\n"

# clean:
# 	@make -C $(LIBFT_DIR) clean
# 	@rm -rf $(OBJS) $(SURPL_O)

# fclean: clean
# 	@make -C $(LIBFT_DIR) fclean
# 	@rm -rf $(VM_NAME) *.out

# re: fclean all