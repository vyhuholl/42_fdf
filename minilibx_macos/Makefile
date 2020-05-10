# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/22 23:12:10 by pbondoer          #+#    #+#              #
#    Updated: 2020/04/18 23:36:06 by sghezn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include libmlx.mk

CFLAGS+=-Wno-deprecated-declarations

all: $(MLX_LIB)

$(MLX_LIB):
	@make -C $(MLX_DIR)
	cp $(MLX_LIB) $(MLX_NAME)

clean:
	make -C $(MLX_DIR) clean
	rm -f $(MLX_NAME)

fclean: clean

re:
	@$(MAKE) clean --no-print-directory
	@$(MAKE) all --no-print-directory
