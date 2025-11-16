/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:53:10 by echatela          #+#    #+#             */
/*   Updated: 2025/11/16 17:57:48 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/*	STD headers		*/
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <sys/time.h>
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
# include "types.h"
# include "scene.h"
# include "init.h"
# include "error.h"
# include "wrapper.h"

#endif
