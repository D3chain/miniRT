# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: echatela <echatela@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/13 13:22:15 by echatela          #+#    #+#              #
#    Updated: 2025/11/14 14:55:00 by echatela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	miniRT
CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -g3 -MMD -MP
SRC_DIR		:=	source
OBJ_DIR		:=	.build
LIBFT_DIR	:=	libft
INCLUDE		:=	include $(LIBFT_DIR)/include
CFLAGS		+=	$(addprefix -I, $(INCLUDE))

ROOT_SRC	:=	main.c

SRC_PATHS	:= \
	$(ROOT_SRC)

SRC			:=	$(addprefix $(SRC_DIR)/,$(SRC_PATHS))

OBJ			:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

DEPS		:=	$(OBJ:.o=.d)

LIBFT		:=	$(LIBFT_DIR)/libft.a

all:	$(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $@ \

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:	clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

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