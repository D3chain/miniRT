/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:46:00 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/16 21:56:03 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "minirt.h"

# ifdef USE_DBL_NUMBER
#  define EPSILON	0.001
#  define COEF_SPEC 0.2
#  define SHININESS 100.0
# else
#  define EPSILON	0.001f
#  define COEF_SPEC 0.2f
#  define SHININESS 100.0f
# endif

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
#  define OVERSAMPLING	4
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
#  if TILE_SIDE != 16 && TILE_SIDE != 32
#   define TILE_SIDE 16
#  endif
# endif

/*													*/
/*	This part defines the motion behavior			*/
/*													*/
# ifdef USE_DBL_NUMBER
#  define ZOOM_FOV_REFERENCE	60.0
#  define ZOOM_BASE_PAN_SPEED	0.5
#  define ZOOM_FAST_PAN_SPEED	2.0
#  define ZOOM_INCREASE_FACTOR	1.1
#  define ZOOM_DECREASE_FACTOR	0.9
#  define ZOOM_MIN_SPEED		0.1f
# else
#  define ZOOM_FOV_REFERENCE	60.0f
#  define ZOOM_BASE_PAN_SPEED	0.5f
#  define ZOOM_FAST_PAN_SPEED	2.0f
#  define ZOOM_INCREASE_FACTOR	1.1f
#  define ZOOM_DECREASE_FACTOR	0.9f
#  define ZOOM_MIN_SPEED		0.1f
#endif

# define ZOOM_TO_PAN_RATIO		10

# define ZOOM_ALIASING_REENABLE_TIME	100

#endif
