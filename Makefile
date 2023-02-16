# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 10:11:17 by marius            #+#    #+#              #
#    Updated: 2023/02/14 18:31:29 by mtissari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CEND			= \033[0m
CGREEN			= \033[0;32m
CYELLOW			= \033[0;33m
CPURPLEB		= \033[1;95m

CC				= gcc
VM_NAME			= corewar
ASM_NAME		= asm
FLAGS			= -Wall -Wextra -Werror


VM_SRC_DIR		= ./srcs/virtualmachine/
VM_SRC_FILES	= main.c \
				read_players.c \
				player_ids.c \
				inits.c \
				prints.c \
				process.c \
				game_loop.c \
				player_validation.c \
				player_validation2.c \
				vm_utils.c \
				flags.c \
				set_statements.c \
				execute.c \
				get_arguments.c

VM_STAT_DIR		= $(VM_SRC_DIR)statements/
VM_STATEMENTS	= add.c \
				aff.c \
				and.c \
				fork.c \
				ld.c \
				ldi.c \
				lfork.c \
				live.c \
				lld.c \
				lldi.c \
				or.c \
				st.c \
				sti.c \
				sub.c \
				xor.c \
				zjmp.c

ASM_SRC_DIR		= ./srcs/asm/
ASM_SRC_FILES	= get_instructions.c \
				get_name_comment.c \
				get_statements.c \
				get_statements2.c \
				get_statements3.c \
				get_statements4.c \
				joinfree.c \
				main.c \
				populate_help.c \
				populate.c \
				scanner.c \
				utils.c \
				utils2.c \
				write_bytes.c \
				write_to_file.c \
				write_utils.c

INC_DIR		= ./includes/

VM_SRC			= $(addprefix $(VM_SRC_DIR), $(VM_SRC_FILES))
VM_SRC_STAT		= $(addprefix $(VM_STAT_DIR), $(VM_STATEMENTS))

VM_OBJ_DIR		= ./vm_obj/
VM_OBJ_FILES	= $(VM_SRC_FILES:.c=.o) $(VM_STATEMENTS:.c=.o)
VM_OBJ			= $(addprefix $(VM_OBJ_DIR), $(VM_OBJ_FILES))

VM_INC_FILES	= virtualmachine.h
VM_INC			= $(addprefix $(INC_DIR), $(VM_INC_FILES))

ASM_SRC			= $(addprefix $(ASM_SRC_DIR), $(ASM_SRC_FILES))

ASM_OBJ_DIR		= ./asm_obj/
ASM_OBJ_FILES	= $(ASM_SRC_FILES:.c=.o)
ASM_OBJ			= $(addprefix $(ASM_OBJ_DIR), $(ASM_OBJ_FILES))

ASM_INC_FILES	= assembler.h
ASM_INC			= $(addprefix $(INC_DIR), $(ASM_INC_FILES))

LIBFT_DIR		= libft/
LIBFT_LIB		= libftprintf.a
LIBFT			= $(addprefix $(LIBFT_DIR), $(LIBFT_LIB))

all : $(VM_NAME) $(ASM_NAME)

$(VM_NAME): $(VM_OBJ) $(VM_INC)
	@make -C $(LIBFT_DIR)
	@echo "$(CYELLOW)Compiling the executable: $(CPURPLEB)$(VM_NAME)$(CEND)"
	@$(CC) -o $(VM_NAME) $(FLAGS) $(VM_OBJ) -I libft/includes/ -I ./includes/ -L. $(LIBFT)
	@echo "$(CGREEN)OK$(CEND)"

$(VM_OBJ_DIR)%.o: $(VM_SRC_DIR)%.c
	@mkdir -p $(VM_OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

$(VM_OBJ_DIR)%.o: $(VM_STAT_DIR)%.c
	@mkdir -p $(VM_OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

$(ASM_NAME): $(LIBFT) $(ASM_OBJ_DIR) $(ASM_OBJ) $(ASM_INC) 
	@echo "$(CYELLOW)Compiling Asm: $(CPURPLEB)$(ASM_NAME)$(CEND)"
	$(CC) -o $(ASM_NAME) $(FLAGS) $(ASM_OBJ) -I libft/includes/ -I ./includes/ -L. $(LIBFT)
	@echo "$(CGREEN)OK$(CEND)"
	
$(ASM_OBJ_DIR)%.o: $(ASM_SRC_DIR)%.c
	@$(CC) $(FLAGS) -c $< -o $@

$(ASM_OBJ_DIR):
	@mkdir -p $(ASM_OBJ_DIR)
	@echo "$(CPURPLEB)$(ASM_OBJ_DIR)$(CGREEN) folder has been created$(CEND)"

clean :
	@make -C $(LIBFT_DIR) clean
	@echo "$(CYELLOW)Removing $(CPURPLEB)$(VM_OBJ_DIR)$(CYELLOW) object folder$(CEND)"
	@rm -rf $(VM_OBJ_DIR)
	@echo "$(CGREEN)OK$(CEND)"
	@echo "$(CYELLOW)Removing $(CPURPLEB)$(ASM_OBJ_DIR)$(CYELLOW) object folder$(CEND)"
	@rm -rf $(ASM_OBJ_DIR)
	@echo "$(CGREEN)OK$(CEND)"

fclean : clean
	@make -C $(LIBFT_DIR) fclean
	@echo "$(CYELLOW)Removing $(CPURPLEB)$(VM_NAME)$(CEND)"
	@rm -rf $(VM_NAME)
	@echo "$(CGREEN)OK$(CEND)"
	@echo "$(CYELLOW)Removing $(CPURPLEB)$(ASM_NAME)$(CEND)"
	@rm -rf $(ASM_NAME)
	@echo "$(CGREEN)OK$(CEND)"

re : fclean all clean all