/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:50 by echatela          #+#    #+#             */
/*   Updated: 2026/01/18 22:20:46 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_real	ft_dblcmp(t_real d1, t_real d2, t_real epsilon)
{
	const t_real	dif = d1 - d2;
	
	if (ft_dabs(dif) < epsilon)
		return (FLT_0);
	return (dif);
}
