#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sghezn <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 10:00:43 by sghezn            #+#    #+#              #
#    Updated: 2019/04/08 17:10:08 by sghezn           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a
HEADER = libft.h
FLAG = -Wall -Wextra -Werror
OPTION = -c -I $(HEADER)

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	gcc $(FLAG) $(OPTION) $(SRC)
	ar rc $(NAME) $(OBJ)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
