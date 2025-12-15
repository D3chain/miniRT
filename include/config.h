/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:46:00 by cgajean           #+#    #+#             */
/*   Updated: 2025/12/15 16:02:05 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "minirt.h"

# define COEF_SPEC 0.75
# define SHININESS 100

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1920
# endif

# ifdef WIN_WIDTH
#  if WIN_WIDTH < 1
#   define WIN_WIDTH 1
#  endif
# endif

# define EPSILON	0.00001

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1080
# endif

# ifdef WIN_HEIGHT
#  if WIN_HEIGHT < 1
#   define WIN_HEIGHT 1
#  endif
# endif

# define IMG_RATIO	((double) WIN_WIDTH / WIN_HEIGHT)

#endif