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


int	get_int(char *str)
{
	size_t	len;
	char	*p = str;
	int		res = 0;
	
	while (!ft_isalnum(*p++))
	;
	
	while(ft_isalnum(*p++))
	res += res * 10 + (*p++ - '0');
}

// double	scan_double(struct s_app *app, const char *str)
// {
// 	int		integer;
// 	int		decimal;
// 	int		len;
// 	double	res;
	
// 	integer = ft_atoi(str);
// 	if (!ft_isdigit(*str))
// 		return (app->status = ERR_PARS, 0.0);
// 	while(ft_isdigit(*str))
// 		++str;
// 	if (*str++ != '.')
// 		return (app->status = ERR_PARS, 0.0);
// 	decimal = ft_atoi(str);
// 	len = ft_nbrlen(decimal);
// 	if (!isnum(*str))
// 		return (app->status = ERR_PARS, 0.0);
// 	while(ft_isdigit(*str))
// 		++str;
// 	if (!(*str == ',' || ft_isspace(*str) || *str == '/0'))
// 		return (app->status = ERR_PARS, 0.0);
// 	res = integer + decimal * pow(10, -len);
// }

int	scan_double(struct s_app *app, double *d, const char *str)
{
	int		i;
	int		j;
	
	i = 0;
	if (!ft_isdigit(*str))
		return (app->status = ERR_PARS, -1);
	*d = ft_atoi(str);
	while(ft_isdigit(str[i]))
		++i;
	if (str[i] == '.')
	{
		if (!ft_isdigit(str[i]))
			return (app->status = ERR_PARS, -1);
		j = i;
		while(ft_isdigit(str[i]))
			++i;
		*d += ft_atoi(&str[j]) * pow(10, -(i - j));
	}
	return (i);
}

t_double3	scan_double3(struct s_app *app, const char *str)
{
	t_double3	res;
	int			i;

	ft_bzero(&res, sizeof(res));
	str += scan_double(app, &res.x, str);
	if (*str != ',')
		return (app->status = ERR_PARS, res);
	str += scan_double(app, &res.y, str);
	if (*str != ',')
		return (app->status = ERR_PARS, res);
	str += scan_double(app, &res.z, str);
	if (*str != 0 && !ft_isspace(*str))
		return (app->status = ERR_PARS, res);
	return (res);
}

