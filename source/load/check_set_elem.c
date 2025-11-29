/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_set_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 10:25:22 by echatela          #+#    #+#             */
/*   Updated: 2025/11/29 11:04:00 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_A(struct s_app *app, const char *line);

int	parse_C(struct s_app *app, const char *line)
{

}

int	parse_L(struct s_app *app, const char *line);
int	parse_pl(struct s_app *app, const char *line);
int	parse_sp(struct s_app *app, const char *line); 
int	parse_cy(struct s_app *app, const char *line);

int	check_get_i_elem(const char *line)
{
	const char	*l_elem[7] = {"A", "C", "L", "pl", "sp", "cy", NULL};
	int			i;

	i = 0;
	while (l_elem[i])
	{
		if (ft_strncmp(l_elem[i], line, ft_strlen(l_elem[i])) == 0)
			return (i);
		i++;
	}
	return (i);
}

int	check_set_elem(struct s_app *app, const char *line)
{
	const int	(*parse_fct[7])(struct s_app *, const char *) = {
		parse_A, parse_C, parse_L, parse_pl, parse_sp, parse_cy, NULL};

	parse_fct[check_get_i_elem(line)](app, line);
	if (app->status)
		return (app->status);
	return (0);
}
