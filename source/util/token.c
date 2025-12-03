/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:52:06 by cgajean           #+#    #+#             */
/*   Updated: 2025/12/03 12:32:34 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*next_tok(const char *str)
{
	while (*str && !ft_isspace(*str))
		str++;
	while (*str && ft_isspace(*str))
		str++;
	return ((char *)str);
}
