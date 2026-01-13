/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:02:09 by echatela          #+#    #+#             */
/*   Updated: 2026/01/13 15:11:55 by cgajean          ###   ########.fr       */
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

struct s_double2
{
    double  x;
    double  y;
};

struct s_double3
{
    double  x;
    double  y;
    double  z;
};

#endif
