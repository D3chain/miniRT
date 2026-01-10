/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:53:10 by echatela          #+#    #+#             */
/*   Updated: 2026/01/10 13:00:03 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/*	STD headers		*/
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <errno.h>

/*	X11 headers		*/
# include <X11/keysym.h>
# include <X11/keysymdef.h>
# include <X11/Xlib.h>
# include <X11/X.h>

/*	MLX headers		*/
# include "mlx.h"
// # include "mlx_int.h"

/*	libft header	*/
# include "libft.h"

/*	Local headers	*/
# include "config.h"
# include "color.h"
# include "types.h"
# include "scene.h"
# include "bvh.h"
# include "app.h"
# include "init.h"
# include "math_util.h"
# include "load.h"
# include "run.h"
# include "error.h"
# include "wrapper.h"
# include "util.h"

#endif
