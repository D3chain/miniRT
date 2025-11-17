# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: echatela <echatela@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/13 13:22:15 by echatela          #+#    #+#              #
#    Updated: 2025/11/17 11:57:21 by echatela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	miniRT
CC			:=	cc
# CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP -g3
CFLAGS		:=	-MMD -MP -g3
SRC_DIR		:=	source
OBJ_DIR		:=	.build
LIBFT_DIR	:=	libft
MLX_DIR		:=	mlx
INCLUDE		:=	include $(LIBFT_DIR)/include $(MLX_DIR) 
CFLAGS		+=	$(addprefix -I, $(INCLUDE))

# /* librairy flags */
CFLAGS		+= -lm
CFLAGS		+= -lX11 -lXext #-lmlx 

ROOT_SRC	:=	main.c init/init_app.c init/init_scene.c wrapper/xmalloc.c wrapper/xopen.c error/err_per.c error/fill.c

SRC_PATHS	:= \
	$(ROOT_SRC)

SRC			:=	$(addprefix $(SRC_DIR)/,$(SRC_PATHS))

OBJ			:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

DEPS		:=	$(OBJ:.o=.d)

LIBFT		:=	$(LIBFT_DIR)/libft.a
MLX			:=	$(MLX_DIR)/libmlx_Linux.a

all:	$(LIBFT) mlx $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

mlx:
	$(MAKE) -C $(MLX_DIR)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $@ \

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean:	clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re:		fclean all

test: all
	@valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--trace-children=yes \
	--log-file=valgrind.log \
	./miniRT
	@echo "\n"
	@cat valgrind.log
	@rm -f valgrind.log

.PHONY: all mlx clean fclean re test
