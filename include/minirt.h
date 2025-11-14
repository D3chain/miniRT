/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:53:10 by echatela          #+#    #+#             */
/*   Updated: 2025/11/14 18:36:19 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <sys/time.h>

# include "libft.h"

# include "types.h"

# include "scene.h"
# include "init.h"

typedef enum e_status
{
	NO_ERR		= 0,
	ERR_SYS		= 1,
	ERR_PARS	= 2
}	t_status;

struct s_data
{
	struct s_scene	scene;

	t_status		status;
};

#endif
