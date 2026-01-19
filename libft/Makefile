# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 10:24:34 by cgajean           #+#    #+#              #
#    Updated: 2026/01/19 18:39:06 by cgajean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIE -MMD -MP -g3

MAIN_DIR = .
SRC_DIR = $(MAIN_DIR)/source
INC_DIR = $(MAIN_DIR)/include
BUILD = $(MAIN_DIR)/build

SRCS = \
		$(SRC_DIR)/ft_skipspaces.c 						\
		$(SRC_DIR)/ft_printf.c 							\
														\
		$(SRC_DIR)/ft_strcpy.c							\
		$(SRC_DIR)/ft_strlen.c 							\
		$(SRC_DIR)/ft_strcmp.c							\
		$(SRC_DIR)/ft_strncmp.c							\
		$(SRC_DIR)/ft_strrcmp.c							\
		$(SRC_DIR)/ft_strrncmp.c 						\
		$(SRC_DIR)/ft_strlcat.c 						\
		$(SRC_DIR)/ft_strlcpy.c 						\
		$(SRC_DIR)/ft_nbrlen.c 							\
		$(SRC_DIR)/ft_nbrlen_base.c 					\
														\
		$(SRC_DIR)/ft_split.c 							\
		$(SRC_DIR)/ft_split_free.c						\
		$(SRC_DIR)/ft_strdup.c 							\
		$(SRC_DIR)/ft_strjoin.c 						\
		$(SRC_DIR)/ft_strnjoin.c 						\
		$(SRC_DIR)/ft_strtrim.c 						\
		$(SRC_DIR)/ft_substr.c 							\
														\
		$(SRC_DIR)/ft_strmapi.c 						\
		$(SRC_DIR)/ft_striteri.c 						\
														\
		$(SRC_DIR)/ft_strstr.c							\
		$(SRC_DIR)/ft_strnstr.c							\
		$(SRC_DIR)/ft_strchr.c 							\
		$(SRC_DIR)/ft_strrchr.c 						\
														\
		$(SRC_DIR)/ft_atoi.c 							\
		$(SRC_DIR)/ft_atoi_base.c 						\
		$(SRC_DIR)/ft_itoa.c 							\
		$(SRC_DIR)/ft_itoa_static.c 					\
														\
		$(SRC_DIR)/ft_bzero.c 							\
		$(SRC_DIR)/ft_calloc.c 							\
		$(SRC_DIR)/ft_realloc.c 						\
														\
		$(SRC_DIR)/ft_isalnum.c							\
		$(SRC_DIR)/ft_isalpha.c							\
		$(SRC_DIR)/ft_isascii.c 						\
		$(SRC_DIR)/ft_isdigit.c 						\
		$(SRC_DIR)/ft_isprint.c 						\
		$(SRC_DIR)/ft_isupper.c 						\
		$(SRC_DIR)/ft_islower.c 						\
		$(SRC_DIR)/ft_isspace.c 						\
		$(SRC_DIR)/ft_isspace_str.c						\
		$(SRC_DIR)/ft_tolower.c 						\
		$(SRC_DIR)/ft_toupper.c 						\
		$(SRC_DIR)/ft_tolower_str.c 					\
		$(SRC_DIR)/ft_toupper_str.c 					\
														\
		$(SRC_DIR)/ft_memchr.c 							\
		$(SRC_DIR)/ft_memcmp.c 							\
		$(SRC_DIR)/ft_memcpy.c 							\
		$(SRC_DIR)/ft_memmove.c 						\
		$(SRC_DIR)/ft_memset.c 							\
														\
		$(SRC_DIR)/ft_putstr.c 							\
		$(SRC_DIR)/ft_puterr.c 							\
		$(SRC_DIR)/ft_putchar.c 						\
														\
		$(SRC_DIR)/ft_putnbr.c 							\
		$(SRC_DIR)/ft_putunbr.c 						\
		$(SRC_DIR)/ft_putnbr_base.c 					\
		$(SRC_DIR)/ft_putunbr_base.c 					\
		$(SRC_DIR)/ft_putaddr_hex.c 					\
														\
		$(SRC_DIR)/ft_putchar_fd.c 						\
		$(SRC_DIR)/ft_putstr_fd.c						\
		$(SRC_DIR)/ft_putendl_fd.c 						\
		$(SRC_DIR)/ft_putnbr_fd.c 						\
														\
		$(SRC_DIR)/gets_next_line.c						\
		$(SRC_DIR)/getd_next_line.c						\
														\
		$(SRC_DIR)/ft_lstnew.c 							\
		$(SRC_DIR)/ft_lstadd_front.c 					\
		$(SRC_DIR)/ft_lstsize.c 						\
		$(SRC_DIR)/ft_lstlast.c 						\
		$(SRC_DIR)/ft_lstadd_back.c 					\
		$(SRC_DIR)/ft_lstdelone.c 						\
		$(SRC_DIR)/ft_lstclear.c 						\
		$(SRC_DIR)/ft_lstiter.c 						\
		$(SRC_DIR)/ft_lstmap.c							\
		$(SRC_DIR)/ft_lstfree.c 						\
														\
		$(SRC_DIR)/ft_toradian.c 						\
		$(SRC_DIR)/ft_dblcmp.c	 						\
		$(SRC_DIR)/ft_dabs.c


OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD)/%.o)
DEPS = $(OBJS:$(%.o=%.d))

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(BUILD)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS)
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re