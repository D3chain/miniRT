/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:03:29 by echatela          #+#    #+#             */
/*   Updated: 2025/11/18 11:04:42 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include "minirt.h"

double		dot(t_double3 a, t_double3 b);
t_double3	dot3(t_double3 a, t_double3 b);
t_double3	plus3(t_double3 a, t_double3 b);
t_double3	minus3(t_double3 a, t_double3 b);

#endif