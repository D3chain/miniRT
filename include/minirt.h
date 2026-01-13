/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:53:10 by echatela          #+#    #+#             */
/*   Updated: 2026/01/13 17:24:40 by cgajean          ###   ########.fr       */
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

/*	X11 headers	*/
# include <X11/keysym.h>
# include <X11/keysymdef.h>
# include <X11/Xlib.h>
# include <X11/X.h>

/*	MLX headers	*/
# include "mlx.h"

/*	libft header	*/
# include "libft.h"

/*	Niveau 1 : Types de base et config (ne dépendent de rien) */
# include "config.h"          // Constantes
# include "minirt_typedef.h"  // Typedefs
# include "types.h"            // Structures de base (t_real2, t_real3)

/*	Niveau 2 : Structures de données (dépendent du niveau 1) */
# include "material.h"
# include "ray.h"              // Structures ray et hit_info
# include "scene.h"            // Structures de scène (camera, light, elems)
# include "bvh.h"              // Structures BVH
# include "phong_effect.h"            // Structures couleur et matériaux

/*	Niveau 3 : Application (dépend de scene et autres) */
# include "app.h"              // Structure principale app

/*	Niveau 4 : Fonctions utilitaires */
# include "math_basic.h"        // Fonctions mathématiques
# include "util.h"             // Fonctions utilitaires diverses
# include "error.h"            // Gestion d'erreurs
# include "wrapper.h"          // Wrappers malloc, etc.

/*	Niveau 5 : Logique métier */
# include "init.h"             // Initialisation
# include "load.h"             // Chargement de scène
# include "run.h"              // Boucle principale

#endif
