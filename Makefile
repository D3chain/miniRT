# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/13 13:22:15 by echatela          #+#    #+#              #
#    Updated: 2025/11/19 15:34:06 by cgajean          ###   ########.fr        #
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

ROOT_SRC	:=	main.c

INIT_SRC	:=	init_app.c init_mlx.c init_scene.c
LOAD_SRC	:=	load_scene.c
RUN_SRC		:=	run_scene.c event.c ray_collision.c ray_cylinder.c draw.c util/closest_hit_dst.c
MATH_SRC	:=	math_util.c polynome2.c
WRAPPER_SRC	:=	xmalloc.c xopen.c
ERROR_SRC	:=	err_per.c fill.c
UTIL_SRC	:=	color.c

SRC_PATHS	:= \
	$(addprefix init/,$(INIT_SRC)) \
	$(addprefix load/,$(LOAD_SRC)) \
	$(addprefix run/,$(RUN_SRC)) \
	$(addprefix math/,$(MATH_SRC)) \
	$(addprefix wrapper/,$(WRAPPER_SRC)) \
	$(addprefix util/,$(UTIL_SRC)) \
	$(addprefix error/,$(ERROR_SRC)) \
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
	./miniRT caca.rt

.PHONY: all mlx clean fclean re test
