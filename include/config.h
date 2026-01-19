/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:46:00 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 13:53:18 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "minirt.h"


# define COEF_SPEC	FLT_0_2
# define SHININESS	FLT_100


//	SCREEN RESOLUTION
# define WIN_WIDTH					1920
# define WIN_HEIGHT					1080
# define IMG_RATIO	((t_real) WIN_WIDTH / WIN_HEIGHT)

//	SAMPLING
# define UPSAMPLING_INIT_ACTIV		true
# define UPSAMPLING					4

# define DOWNSAMPLING_INIT_ACTIV	false
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
# define ZOOM_FAST_PAN_SPEED		FLT_2

# define ZOOM_INCREASE_FACTOR		FLT_1_1
# define ZOOM_DECREASE_FACTOR		FLT_0_9
# define ZOOM_MIN_SPEED				FLT_0_1

# define CAMERA_VIEW_FACTOR			FLT_0_5

//	PRINT
# define MAX_NAME_LEN				128

#endif
