# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marius <marius@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 09:27:03 by mangheli          #+#    #+#              #
#    Updated: 2022/12/09 09:16:59 by marius           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

SRCS = ft_atoi ft_bzero ft_isalnum ft_isalpha ft_isascii ft_isdigit \
		ft_isprint ft_itoa ft_lstadd ft_lstdel ft_lstdelone ft_lstiter \
		ft_lstmap ft_lstnew ft_memalloc ft_memccpy ft_memchr ft_memcmp \
		ft_memcpy ft_memdel ft_memmove ft_memset ft_putchar_fd ft_putchar \
		ft_putendl_fd ft_putendl ft_putnbr_fd ft_putnbr ft_putstr_fd \
		ft_putstr ft_strcat ft_strchr ft_strclr ft_strcmp ft_strcpy \
		ft_strdel ft_strdup ft_strequ ft_striter ft_striteri ft_strjoin \
		ft_strlcat ft_strlen ft_strmap ft_strmapi ft_strncat ft_strncpy \
		ft_strnequ ft_strnew ft_strnstr ft_strsplit ft_strstr ft_strsub \
		ft_strtrim ft_tolower ft_toupper ft_strrchr ft_strncmp \
		ft_emptyspace ft_lstaddlast ft_utoa ft_strnlen get_next_line \
		ft_strupdate ft_wordcounter ft_strtab_free ft_strndup 
SRC := $(addsuffix .c, $(SRCS))
INC := includes
CFLAGS := -Wall -Wextra -Werror -O2
LIBS := $(SRC:%.c=%.o)

all: $(NAME)

$(NAME):
	gcc -c $(SRC) -I $(INC) $(CFLAGS)
	ar rc $(NAME)  $(LIBS)
	ranlib $(NAME)

clean:
		/bin/rm -f $(LIBS)

fclean:	clean
		/bin/rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re
