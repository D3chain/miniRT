/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:22:52 by echatela          #+#    #+#             */
/*   Updated: 2025/12/16 16:46:33 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_double3(t_double3 d, char *text)
{
	if (text)
		printf("%s", text);
	printf("(%lf, %lf, %lf)\n", d.x, d.y, d.z);
}

void	print_color(t_color color, char *text)
{
	if (text)
		printf("%s", text);
	printf("(r=%du, g=%du, b=%du)\n", color.s_rgb.r, color.s_rgb.g, color.s_rgb.b);
}
