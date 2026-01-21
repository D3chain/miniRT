/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:53:10 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 16:31:05 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define _GNU_SOURCE

/*	STD headers	*/
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdint.h>
# include <errno.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

/*	X11 headers	*/
# include <X11/keysym.h>
# include <X11/keysymdef.h>
# include <X11/Xlib.h>
# include <X11/X.h>

/*	MLX headers	*/
# include "mlx.h"

/*	libft header	*/
# include "libft.h"

# include "minirt_typedef.h"
# include "config.h"
# include "types.h"

# include "shapes.h"

# include "material.h"
# include "ray.h"
# include "scene.h"
# include "bvh.h"
# include "phong_effect.h"

# include "run.h"
# include "app.h"

# include "mathematics.h"
# include "print.h"
# include "error.h"
# include "wrapper.h"

# include "load.h"

#endif
