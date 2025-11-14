/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:13:13 by cgajean           #+#    #+#             */
/*   Updated: 2025/11/13 18:09:20 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_puterr(char *errmsg)
{
	ssize_t	len;

	if (!errmsg)
		return (0);
	len = (ssize_t) ft_strlen(errmsg);
	write(STDERR_FILENO, errmsg, len);
	return (len);
}
