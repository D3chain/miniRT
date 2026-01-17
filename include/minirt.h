/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:53:10 by echatela          #+#    #+#             */
/*   Updated: 2026/01/17 12:41:59 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/*	STD headers	*/
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <errno.h>
# include <pthread.h>
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

# include "flt_constants.h"
# include "minirt_typedef.h"  // Typedefs
# include "config.h"          // Constantes
# include "types.h"            // Structures de base (t_real2, t_real3)

# include "material.h"
# include "ray.h"              // Structures ray et hit_info
# include "scene.h"            // Structures de scène (camera, light, elems)
# include "bvh.h"              // Structures BVH
# include "phong_effect.h"            // Structures couleur et matériaux

# include "app.h"              // Structure principale app

# include "mathematics.h"        // Fonctions mathématiques
# include "util.h"             // Fonctions utilitaires diverses
# include "error.h"            // Gestion d'erreurs
# include "wrapper.h"          // Wrappers malloc, etc.

// # include "init.h"             // Initialisation
# include "load.h"             // Chargement de scène
# include "run.h"              // Boucle principale

#endif
