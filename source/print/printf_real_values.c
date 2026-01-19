/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:22:52 by echatela          #+#    #+#             */
/*   Updated: 2026/01/16 22:00:05 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_real3(t_real3 d, char *text)
{
	static const int	t_real_size = sizeof(t_real);
	
	printf("%s", text);
	if (t_real_size == sizeof(float))
		printf("%.3f,%.3f,%.3f\n", d.x, d.y, d.z);
	
	else
		printf("%.3lf,%.3lf,%.3lf\n", d.x, d.y, d.z);
}

void	print_color(t_color color, char *text)
{
	if (text)
		printf("%s", text);
	printf("(r=%du, g=%du, b=%du)\n", color.s_rgb.r, color.s_rgb.g, color.s_rgb.b);
}

void	print_color_linear(t_color_linear color, char *text)
{
	if (text)
		printf("%s", text);
	printf("(r=%lf, g=%lf, b=%lf)\n", color.r, color.g, color.b);
}
