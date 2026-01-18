/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:46:00 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/18 12:42:52 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "minirt.h"

# define EPSILON	FLT_0_1 / FLT_10
# define COEF_SPEC	FLT_0_2
# define SHININESS	FLT_100

/*										*/
/*	This part defines the screen size	*/
/*										*/
# ifndef WIN_WIDTH
#  define WIN_WIDTH 1920
# endif

# ifdef WIN_WIDTH
#  if WIN_WIDTH < 1
#   define WIN_WIDTH 800
#  endif
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1080
# endif

# ifdef WIN_HEIGHT
#  if WIN_HEIGHT < 1
#   define WIN_HEIGHT 600
#  endif
# endif

# define IMG_RATIO	((t_real) WIN_WIDTH / WIN_HEIGHT)

/*																*/
/*	This part defines the behavior of the antialiasing system	*/
/*																*/
# ifndef OVERSAMPLING
#  define OVERSAMPLING	16
# endif

# ifdef OVERSAMPLING
#  if OVERSAMPLING < 1
#   define OVERSAMPLING 4
#  endif
# endif


/*																*/
/*	This part defines the behavior of the bvh grouping system	*/
/*																*/
# ifndef BVH_MIN_ELEM
#  define BVH_MIN_ELEM	4
# endif

# ifdef BVH_MIN_ELEM
#  if BVH_MIN_ELEM < 1
#   define BVH_MIN_ELEM 1
#  endif
# endif

/*																*/
/*	This part defines the size of the thread's tiles			*/
/*																*/
# ifndef TILE_SIDE
#  define TILE_SIDE	32
# endif

# ifdef TILE_SIDE
#  if TILE_SIDE < 1
#   define TILE_SIDE 16
#  endif
# endif

/*													*/
/*	This part defines the motion behavior			*/
/*													*/

# define FOV_MODIFY				FLT_5
# define FOV_REFERENCE			FLT_60
# define FOV_MIN				FOV_MODIFY
# define FOV_MAX				FLT_100 + FLT_75

# define OBJ_DRAG_DIV_FACTOR	FLT_5

# define ZOOM_BASE_PAN_SPEED	FLT_0_5
# define ZOOM_FAST_PAN_SPEED	FLT_2

# ifdef USE_DBL_NUMBER
#  define ZOOM_INCREASE_FACTOR		1.1
# else
#  define ZOOM_INCREASE_FACTOR		1.1f
# endif

# define ZOOM_DECREASE_FACTOR	FLT_0_9
# define ZOOM_MIN_SPEED			FLT_0_1

# ifdef USE_DBL_NUMBER
#  define MOUSE_SENSITIVITY		0.02
# else
#  define MOUSE_SENSITIVITY		0.02f
# endif

# define ZOOM_TO_PAN_RATIO		10

# define ZOOM_ALIASING_REENABLE_TIME	100

# define CAMERA_VIEW_FACTOR	FLT_0_5

#endif
