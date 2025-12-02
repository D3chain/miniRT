/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_double3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:18:01 by echatela          #+#    #+#             */
/*   Updated: 2025/11/29 11:27:12 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	scan_color(struct s_app *app, t_color *res, const char *str)
{
	int	i;

	i += scan_uint8_t(app, &res->s_rgb.r, str);
	str += i;
	if (app->status || str[i] != ',')
		return (app->status = ERR_PARS, -1);
	i += scan_uint8_t(app, &res->s_rgb.g, str);
	str += i;
	if (app->status || str[i] != ',')
		return (app->status = ERR_PARS, -1);
	i += scan_uint8_t(app, &res->s_rgb.b, str);
	if (app->status)
		return (-1);
	return (i);
}

int	scan_int(struct s_app *app, int *res, const char *str)
{
	int	i;

	if (!ft_isdigit(*str))
		return (app->status = ERR_PARS, -1);
	i = 0;
	*res = ft_atoi(str);
	while (ft_isdigit(str[i]))
		i++;
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

int	scan_double(struct s_app *app, double *res, const char *str)
{
	int		i;
	int		j;
	
	i = 0;
	if (!ft_isdigit(*str))
		return (app->status = ERR_PARS, -1);
	*res = ft_atoi(str);
	while(ft_isdigit(str[i]))
		++i;
	if (str[i] == '.')
	{
		if (!ft_isdigit(str[i]))
			return (app->status = ERR_PARS, -1);
		j = i;
		while(ft_isdigit(str[i]))
			++i;
		*res += ft_atoi(&str[j]) * pow(10, -(i - j));
	}
	return (i);
}

int	scan_double3(struct s_app *app, t_double3 *res, const char *str)
{
	int			i;

	ft_bzero(res, sizeof(*res));
	i = scan_double(app, &res->x, str);
	str += i;
	if (*str != ',')
		return (app->status = ERR_PARS, i);
	i += scan_double(app, &res->y, str);
	str += i;
	if (*str != ',')
		return (app->status = ERR_PARS, i);
	i += scan_double(app, &res->z, str);
	str += i;
	if (*str != 0 && !ft_isspace(*str))
		return (app->status = ERR_PARS, i);
	return (i);
}
