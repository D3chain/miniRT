# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/19 10:22:57 by cgajean           #+#    #+#              #
#    Updated: 2026/01/20 20:36:08 by cgajean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	miniRT
CC			:=	cc
CFLAGS		:=	-MMD -MP -g3 -Wall -Wextra -Werror # -ffast-math -O3 -flto -march=native -finline-functions -funroll-loops #-pg
SRC_DIR		:=	source
OBJ_DIR		:=	.build
LIBFT_DIR	:=	libft
MLX_DIR		:=	mlx
INCLUDE		:=	include $(LIBFT_DIR)/include $(MLX_DIR) 
CFLAGS		+=	$(addprefix -I, $(INCLUDE))

# /* librairy flags */
LDLIBS		+= -lXext -lX11 -lm -lbsd

ROOT_SRC	:=	main.c

# Application core
APP_SRC		:=	init_app.c															\
				cleanup_app.c

# BVH (Bounding Volume Hierarchy)
BVH_SRC		:=	bvh_build.c															\
				bvh_destroy.c														\
				elem_bounding_box.c													\
				bound_boxes.c														\
				sort_elems.c														\
				collision_aabb.c													\
				any_hit.c

# Colors and lighting
COLOR_SRC	:=	color_linear_conversion.c											\
				color_linear.c														\
				phong_effect.c

# Error handling
ERROR_SRC	:=	err_per.c															\
				fill.c

# Scene loading
LOAD_SRC	:=	load_scene.c														\
				scan_rcal.c															\
				scan_shapes.c														\
				scan_material.c														\
				scan_numbers.c

# Math utilities
MATH_SRC	:=	polynome2.c															\
				vec_op_1.c															\
				vec_op_2.c															\
				vec_op_3.c

# Events
EVENT_SRC	:=	event/event_keyboard.c												\
				event/event_mouse.c													\
				event/event_mouse_motion.c

# Event updates
UPDATE_SRC	:=	event/update/update_antialiasing.c									\
				event/update/update_zoom_speed.c									\
				event/update/update_mouse.c											\
				event/update/update_camera.c										\
				event/update/update_downsampling.c									\
				event/update/update_shapes_coord.c


# Ray tracing
RAY_SRC		:=	ray/init_ray.c														\
				ray/ray_hit.c														\
				ray/ray_hit_sphere.c												\
				ray/ray_hit_cylinder.c												\
				ray/ray_hit_plane.c													\
				ray/ray_hit_cone.c													\
				ray/closest_hit_dst.c

# Rendering
RENDER_SRC	:=	render/render_routine.c												\
				render/draw_pixel_to_img.c											\
				render/antialiasing.c												\
				render/trace.c														\
				render/basic_render.c

# Combine run sources
RUN_SRC		:=	run_scene.c															\
				$(EVENT_SRC)														\
				$(UPDATE_SRC)														\
				$(RAY_SRC)															\
				$(RENDER_SRC)

# Setup
SETUP_SRC	:=	setup_rcal.c														\
				setup_viewport.c													\
				setup_shapes.c

# Utilities
PRINT_SRC	:=	print_bvh_tree.c													\
				print_map.c															\
				print_rcal.c														\
				print_shapes.c														\
				print_shape_material.c												\
				print_parameters.c													\
				printf_real_values.c

# Wrappers
WRAPPER_SRC	:=	xmalloc.c															\
				xcalloc.c															\
				xstrdup.c															\
				xopen.c

SRC_PATHS	:=	$(addprefix app/,$(APP_SRC))										\
				$(addprefix bvh/,$(BVH_SRC))										\
				$(addprefix color/,$(COLOR_SRC))									\
				$(addprefix error/,$(ERROR_SRC))									\
				$(addprefix load/,$(LOAD_SRC))										\
				$(addprefix math/,$(MATH_SRC))										\
				$(addprefix run/,$(RUN_SRC))										\
				$(addprefix setup/,$(SETUP_SRC))									\
				$(addprefix print/,$(PRINT_SRC))									\
				$(addprefix wrapper/,$(WRAPPER_SRC))								\
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
