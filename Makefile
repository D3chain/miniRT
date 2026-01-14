# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/13 13:22:15 by echatela          #+#    #+#              #
#    Updated: 2026/01/14 13:23:02 by cgajean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	miniRT
CC			:=	cc
# CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP -g3
CFLAGS		:=	-MMD -MP -g3 -ffast-math -O3 -flto -march=native -finline-functions -funroll-loops #-pg
SRC_DIR		:=	source
OBJ_DIR		:=	.build
LIBFT_DIR	:=	libft
MLX_DIR		:=	mlx
INCLUDE		:=	include $(LIBFT_DIR)/include $(MLX_DIR) 
CFLAGS		+=	$(addprefix -I, $(INCLUDE))

# /* librairy flags */
LDLIBS		+= -lXext -lX11 -lm -lbsd

ROOT_SRC	:=	main.c

INIT_SRC	:=	init_app.c
LOAD_SRC	:=	load_scene.c scan_CAL.c scan_elem.c scan_numbers.c complete_CAL.c complete_elem.c
RUN_SRC		:=	run_scene.c	\
				event.c	\
				bvh/bvh_build.c bvh/elem_bounding_box.c bvh/bound_boxes.c bvh/sort_elems.c bvh/collision_aabb.c bvh/any_hit.c bvh/print_tree.c	\
				ray/init_ray.c ray/ray_hit.c ray/ray_hit_sphere.c ray/ray_hit_cylinder.c ray/ray_hit_plane.c ray/ray_hit_cone.c	\
				render/render.c render/draw_pixel_to_img.c render/antialiasing.c render/trace.c render/basic_render.c
MATH_SRC	:=	polynome2.c vec_op_1.c vec_op_2.c vec_op_3.c
WRAPPER_SRC	:=	xmalloc.c xcalloc.c xopen.c
ERROR_SRC	:=	err_per.c fill.c
COLOR_SRC	:=	color_linear_conversion.c color_linear.c tone_mapping.c fresnel_schlick.c phong_effect.c	\
				util/closest_hit_dst.c
UTIL_SRC	:=	token.c print.c randomize_material.c

SRC_PATHS	:= \
	$(addprefix init/,$(INIT_SRC)) 			\
	$(addprefix load/,$(LOAD_SRC)) 			\
	$(addprefix run/,$(RUN_SRC)) 			\
	$(addprefix math/,$(MATH_SRC)) 			\
	$(addprefix wrapper/,$(WRAPPER_SRC)) 	\
	$(addprefix util/,$(UTIL_SRC)) 			\
	$(addprefix error/,$(ERROR_SRC)) 		\
	$(addprefix color/,$(COLOR_SRC)) 		\
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
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(LDLIBS) -o $@ \

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
	./miniRT file.rt

.PHONY: all mlx clean fclean re test
