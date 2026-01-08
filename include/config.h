/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:46:00 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/08 11:51:00 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "minirt.h"

# define EPSILON	0.00001

# define COEF_SPEC 0.75
# define SHININESS 100

/*										*/
/*	This part defines the screen size	*/
/*										*/
# ifndef WIN_WIDTH
#  define WIN_WIDTH 800
# endif

# ifdef WIN_WIDTH
#  if WIN_WIDTH < 1
#   define WIN_WIDTH 800
#  endif
# endif


# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 600
# endif

# ifdef WIN_HEIGHT
#  if WIN_HEIGHT < 1
#   define WIN_HEIGHT 600
#  endif
# endif

# define IMG_RATIO	((double) WIN_WIDTH / WIN_HEIGHT)

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

#endif
