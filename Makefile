# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: echatela <echatela@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/13 13:22:15 by echatela          #+#    #+#              #
#    Updated: 2025/11/13 13:35:23 by echatela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	miniRT
CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
SRC_DIR	:=	src
OBJ_DIR	:=	obj
INCLUDE	:=	include
CFLAGS	+=	$(addprefix -I, $(INC_DIRS))

ROOT_SRC	:=	main.c

SRC	:=	$(addprefix $(SRC_DIR)/,\
	$(ROOT_SRC))