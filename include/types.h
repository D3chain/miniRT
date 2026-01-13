/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:02:09 by echatela          #+#    #+#             */
/*   Updated: 2026/01/13 16:54:10 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

enum e_status
{
    ERR_NONE    = 0,
    ERR_SYS     = 1,
    ERR_MLX     = 2,
    ERR_PARS    = 3
};

struct s_real2
{
    t_real  x;
    t_real  y;
};

struct s_real3
{
    t_real  x;
    t_real  y;
    t_real  z;
};

struct s_int2
{
	int	x;
	int	y;
};

struct s_int3
{
	int	x;
	int	y;
	int	z;
};

#endif
