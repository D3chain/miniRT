/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_numbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:14:17 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 20:26:48 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	scan_color(struct s_app *app, t_color *res, const char *str)
{
	int	i;

	i = 0;
	i += scan_uint8_t(app, &res->s_rgb.r, &str[i]);
	if (app->status || str[i++] != ',')
		return (app->status = ERR_PARS, -1);
	i += scan_uint8_t(app, &res->s_rgb.g, &str[i]);
	if (app->status || str[i++] != ',')
		return (app->status = ERR_PARS, -1);
	i += scan_uint8_t(app, &res->s_rgb.b, &str[i]);
	if (app->status)
		return (-1);
	return (i);
}

int	scan_int(struct s_app *app, int *res, const char *str)
{
	int	i;

	i = 0;
	if (*str == '-')
		++i;
	if (!ft_isdigit(*str))
		return (app->status = ERR_PARS, -1);
	i = 0;
	*res = ft_atoi(str);
	while (ft_isdigit(str[i]))
		++i;
	return (i);
}

int	scan_uint8_t(struct s_app *app, uint8_t *res, const char *str)
{
	int	i;

	if (!ft_isdigit(*str))
		return (app->status = ERR_PARS, -1);
	i = 0;
	*res = (uint8_t) ft_atoi(str);
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}

int	scan_t_real(struct s_app *app, t_real *res, const char *str)
{
	int				i;
	int				j;
	int				sign;

	sign = 1;
	i = 0;
	if (str[i] == '-' && ++i)
		sign = -1;
	if (!ft_isdigit(str[i]))
		return (app->status = ERR_PARS, -1);
	*res = ft_atoi(str);
	while (ft_isdigit(str[i]))
		++i;
	if (str[i] == '.')
	{
		if (!ft_isdigit(str[++i]))
			return (app->status = ERR_PARS, -1);
		j = i;
		while (ft_isdigit(str[i]))
			++i;
		*res += sign * ft_atoi(&str[j]) * pow(FLT_10, j - i);
	}
	return (i);
}

int	scan_t_real3(struct s_app *app, t_real3 *res, const char *str)
{
	int			i;

	i = scan_t_real(app, &res->x, str);
	if (app->status)
		return (-1);
	if (str[i++] != ',')
		return (app->status = ERR_PARS, -1);
	i += scan_t_real(app, &res->y, &str[i]);
	if (app->status)
		return (-1);
	if (str[i++] != ',')
		return (app->status = ERR_PARS, -1);
	i += scan_t_real(app, &res->z, &str[i]);
	if (app->status)
		return (-1);
	if (str[i] != 0 && !ft_isspace(str[i]))
		return (app->status = ERR_PARS, -1);
	return (i);
}
