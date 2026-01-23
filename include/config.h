/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:46:00 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/23 11:40:42 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "minirt.h"

//	DFL MATERIAL
# define DFL_KA						FLT_0_1
# define DFL_KD						FLT_0_7
# define DFL_KS						FLT_0_2
# define DFL_SHINE					FLT_100
# define DFL_IOR					FLT_1_5

# define MIN_KA   					FLT_0
# define MIN_KD   					FLT_0
# define MIN_KS   					FLT_0
# define MIN_SHINE					FLT_1
# define MIN_IOR  					FLT_1

# define MAX_K_SUM					FLT_1_1

//	SCREEN RESOLUTION
# define WIN_WIDTH					1440
# define WIN_HEIGHT					900

//	SAMPLING
# define UPSAMPLING_INIT_ACTIV		1
# define UPSAMPLING					4

# define DOWNSAMPLING_INIT_ACTIV	0
# define DOWNSAMPLING				8
# define MAX_DOWNSAMPLING_RATE		32
# define MIN_DOWNSAMPLING_RATE		2

//	BINARY VOLUME HIERARCHY
# define BVH_MIN_ELEM				4

//	RENDER
# define TILE_SIDE					32

# define FOV_MODIFY					FLT_5
# define FOV_REFERENCE				FLT_60
# define FOV_MIN					FOV_MODIFY
# define FOV_MAX					FLT_175

# define IDLE_SCROLL_REENABLE_TILE	100

//	MOUSE
# define MOUSE_SENSITIVITY			FLT_0_02
# define ZOOM_TO_PAN_RATIO			10

# define OBJ_DRAG_DIV_FACTOR		FLT_0_2

# define ZOOM_BASE_PAN_SPEED		FLT_0_5
# define ZOOM_FAST_PAN_SPEED		FLT_50

# define ZOOM_INCREASE_FACTOR		FLT_1_1
# define ZOOM_DECREASE_FACTOR		FLT_0_9
# define ZOOM_MIN_SPEED				FLT_0_1

# define CAMERA_VIEW_FACTOR			FLT_0_3

//	PRINT
# define MAX_NAME_LEN				64

#endif
