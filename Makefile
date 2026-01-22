# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/19 10:22:57 by cgajean           #+#    #+#              #
#    Updated: 2026/01/22 14:09:52 by cgajean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	miniRT
CC			:=	cc
CFLAGS		:=	-MMD -MP -Wall -Wextra -Werror -g3
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
				sort_shapes.c														\
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
				scan_file_line.c													\
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
RAY_SRC		:=	init_ray.c															\
				ray_hit.c															\
				ray_hit_sphere.c													\
				ray_hit_cylinder.c													\
				ray_hit_plane.c														\
				ray_hit_cone_1.c													\
				ray_hit_cone_2.c													\
				closest_hit_dst.c

# Rendering
RENDER_SRC	:=	render/render_routine.c												\
				render/render_tile_downsampled.c									\
				render/draw_pixel_to_img.c											\
				render/antialiasing.c												\
				render/trace.c														\
				render/basic_render.c

# Setup
SETUP_SRC	:=	setup/setup_rcal.c													\
				setup/setup_viewport.c												\
				setup/setup_shapes.c				

# Combine run sources
RUN_SRC		:=	run_scene.c															\
				$(EVENT_SRC)														\
				$(UPDATE_SRC)														\
				$(RENDER_SRC)														\
				$(SETUP_SRC)

# Utilities
PRINT_SRC	:=	print_bvh_tree.c													\
				print_map.c															\
				print_rcal.c														\
				print_planes.c														\
				print_shapes.c														\
				print_shape_material.c												\
				print_parameters.c													\
				print_real_values.c

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
				$(addprefix ray/,$(RAY_SRC))										\
				$(addprefix run/,$(RUN_SRC))										\
				$(addprefix print/,$(PRINT_SRC))									\
				$(addprefix wrapper/,$(WRAPPER_SRC))								\
				$(ROOT_SRC)

SRC			:=	$(addprefix $(SRC_DIR)/,$(SRC_PATHS))

OBJ			:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

DEPS		:=	$(OBJ:.o=.d)

LIBFT		:=	$(LIBFT_DIR)/libft.a
MLX			:=	$(MLX_DIR)/libmlx_Linux.a

# check-mode:
# 	if [PRO_FLAG = "-DLOAD_PRO"]; then \
# 		$(MAKE) clean_pro \
# 	fi

# all:	check-mode
all:	PRO_FLAG = ""
all:	CFLAGS_OPT = ""
all:	$(LIBFT) mlx $(NAME)

pro:	clean_pro
pro:	PRO_FLAG = -DLOAD_PRO
pro:	CFLAGS_OPT = -ffast-math -O3 -flto -march=native -finline-functions -funroll-loops
pro:	$(LIBFT) mlx $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

mlx:
	$(MAKE) -C $(MLX_DIR)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(CFLAGS_OPT) $(OBJ) $(PRO_FLAG) $(LIBFT) $(MLX) $(LDLIBS) -o $@ \

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CFLAGS_OPT) $(PRO_FLAG) -c $< -o $@

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

clean_pro:
	rm -rf $(OBJ_DIR)
	rm -rf $(NAME)

test: all
	@valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--trace-children=yes \
	./miniRT file.rt

.PHONY: all pro mlx clean fclean re test clean_pro
